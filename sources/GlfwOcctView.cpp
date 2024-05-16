#include "GlfwOcctView.h"
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"


namespace
{
    //! Convert GLFW mouse button into Aspect_VKeyMouse.
    static Aspect_VKeyMouse mouseButtonFromGlfw(int theButton)
    {
        switch (theButton)
        {
        case GLFW_MOUSE_BUTTON_LEFT:   return Aspect_VKeyMouse_LeftButton;
        case GLFW_MOUSE_BUTTON_RIGHT:  return Aspect_VKeyMouse_RightButton;
        case GLFW_MOUSE_BUTTON_MIDDLE: return Aspect_VKeyMouse_MiddleButton;
        }
        return Aspect_VKeyMouse_NONE;
    }

    //! Convert GLFW key modifiers into Aspect_VKeyFlags.
    static Aspect_VKeyFlags keyFlagsFromGlfw(int theFlags)
    {
        Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
        if ((theFlags & GLFW_MOD_SHIFT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_SHIFT;
        }
        if ((theFlags & GLFW_MOD_CONTROL) != 0)
        {
            aFlags |= Aspect_VKeyFlags_CTRL;
        }
        if ((theFlags & GLFW_MOD_ALT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_ALT;
        }
        if ((theFlags & GLFW_MOD_SUPER) != 0)
        {
            aFlags |= Aspect_VKeyFlags_META;
        }
        return aFlags;
    }
}

// ================================================================
// Function : GlfwOcctView
// Purpose  :
// ================================================================
GlfwOcctView::GlfwOcctView()
{
    myInterface = std::make_unique<InterfaceCAD>(this);
}

// ================================================================
// Function : ~GlfwOcctView
// Purpose  :
// ================================================================
GlfwOcctView::~GlfwOcctView()
{

}

// ================================================================
// Function : toView
// Purpose  :
// ================================================================
GlfwOcctView* GlfwOcctView::toView(GLFWwindow* theWin)
{
    return static_cast<GlfwOcctView*>(glfwGetWindowUserPointer(theWin));
}

// ================================================================
// Function : errorCallback
// Purpose  :
// ================================================================
void GlfwOcctView::errorCallback(int theError, const char* theDescription)
{
    Message::DefaultMessenger()->Send(TCollection_AsciiString("Error") + theError + ": " + theDescription, Message_Fail);
}

// ================================================================
// Function : run
// Purpose  :
// ================================================================
void GlfwOcctView::run()
{
    initWindow(1366, 768, "Демонстрация возможностей: GLFW+OpenCascade7.8+ImGUI");
    initViewer();
    myInterface->initGui(myOcctWindow);
    initDemoScene();
    if (myView.IsNull())
    {
        return;
    }
    myView->MustBeResized();
    myOcctWindow->Map();
    mainloop();
    cleanup();
}

// ================================================================
// Function : initWindow
// Purpose  :
// ================================================================
void GlfwOcctView::initWindow(int theWidth, int theHeight, const char* theTitle)
{
    glfwSetErrorCallback(GlfwOcctView::errorCallback);
    glfwInit();
    const bool toAskCoreProfile = true;
    if (toAskCoreProfile)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#if defined (__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    myOcctWindow = new GlfwOcctWindow(theWidth, theHeight, theTitle);
    glfwSetWindowUserPointer(myOcctWindow->getGlfwWindow(), this);

    // window callback
    glfwSetWindowSizeCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onResizeCallback);
    glfwSetFramebufferSizeCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onFBResizeCallback);

    // mouse callback
    glfwSetScrollCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseScrollCallback);
    glfwSetMouseButtonCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseButtonCallback);
    glfwSetCursorPosCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseMoveCallback);
}

// ================================================================
// Function : initViewer
// Purpose  :
// ================================================================
#include <Prs3d_DatumAspect.hxx>
#include <AIS_ViewCube.hxx>
void GlfwOcctView::initViewer()
{
    if (myOcctWindow.IsNull()
        || myOcctWindow->getGlfwWindow() == nullptr)
    {
        return;
    }

    Handle(OpenGl_GraphicDriver) aGraphicDriver
        = new OpenGl_GraphicDriver(myOcctWindow->GetDisplay(), Standard_False);
    aGraphicDriver->SetBuffersNoSwap(Standard_True);

    Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);
    aViewer->SetDefaultLights();
    aViewer->SetLightOn();
    aViewer->SetDefaultTypeOfView(V3d_PERSPECTIVE);

    //grid param
    // gp_Ax3 Ax3(gp_Pnt(0,0,0), gp_Dir(0,0,1));
    // aViewer->SetPrivilegedPlane(Ax3);
    // constexpr Standard_Real CustomCellSize = 10;
    // aViewer->SetRectangularGridValues(0, 0, CustomCellSize, CustomCellSize, 0);
    // aViewer->SetRectangularGridGraphicValues(1000*CustomCellSize + 1, 1000*CustomCellSize + 1, CustomCellSize);
    // aViewer->ActivateGrid (Aspect_GT_Rectangular, Aspect_GDM_Lines);

    aViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
    myView = aViewer->CreateView();
    myView->SetImmediateUpdate(Standard_False);
    myView->SetWindow(myOcctWindow, myOcctWindow->NativeGlContext());
    //myView->ChangeRenderingParams().ToShowStats = Standard_True;
    myContext = new AIS_InteractiveContext(aViewer);

    theViewCube = new AIS_ViewCube();
    const Handle(Prs3d_Drawer)& aDrawer = theViewCube->Attributes();
    aDrawer->SetDatumAspect (new Prs3d_DatumAspect());
    const Handle(Prs3d_DatumAspect)& aDatumAsp = aDrawer->DatumAspect();
    aDatumAsp->TextAspect (Prs3d_DatumParts_XAxis)->SetColor (Quantity_NOC_RED);
    aDatumAsp->TextAspect (Prs3d_DatumParts_YAxis)->SetColor (Quantity_NOC_GREEN);
    aDatumAsp->TextAspect (Prs3d_DatumParts_ZAxis)->SetColor (Quantity_NOC_BLUE);

    theViewCube->SetColor(Quantity_NOC_ANTIQUEWHITE);
    theViewCube->SetSize(50,true);
    theViewCube->SetTransformPersistence(
        new Graphic3d_TransformPers(
            Graphic3d_TMF_TriedronPers,
            Aspect_TOTP_RIGHT_LOWER,
            Graphic3d_Vec2i(100, 100))); //Coord position cube from corner

}


#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <math.h>
#include <gp_Circ.hxx>
#include <Geom_BSplineCurve.hxx>

#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Approx_Curve3d.hxx>

#include <gp_Vec.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <gp_Ax2.hxx>

#include <GeomConvert.hxx>
#include <Geom_BezierCurve.hxx>


#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineSurface.hxx>


#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>

#include <AIS_ViewCube.hxx>

#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopoDS.hxx>

#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include "spdlog/include/spdlog/spdlog.h"
// ================================================================
// Function : initDemoScene
// Purpose  :
// ================================================================
void GlfwOcctView::initDemoScene()
{
    if (myContext.IsNull())
    {
        return;
    }
    myView->TriedronDisplay (Aspect_TOTP_LEFT_LOWER, Quantity_NOC_TOMATO3, 0.08, V3d_WIREFRAME);

    TopoDS_Shape cube1 = BRepPrimAPI_MakeBox(gp_Pnt(-25, -25, 0.0), gp_Pnt(0, 0, 25)).Shape();
    TopoDS_Shape cube2 = BRepPrimAPI_MakeBox(gp_Pnt(50, 50, 0.0), gp_Pnt(0, 0, 50)).Shape();
    TopoDS_Shape ShapeFuseCube1 = BRepAlgoAPI_Fuse(cube1, cube2);
    Handle(AIS_Shape) result = new AIS_Shape(ShapeFuseCube1);
    result->SetMaterial( Graphic3d_NOM_CHROME);
    result->SetDisplayMode(AIS_Shaded);
    myContext->Display(result, AIS_Shaded, 0, false);

}
// ================================================================
// Function : mainloop
// Purpose  :
// ================================================================
void GlfwOcctView::mainloop()
{
    while (!glfwWindowShouldClose(myOcctWindow->getGlfwWindow()))
    {
        glfwWaitEvents();
        if (!myView.IsNull())
        {
            myContext->Display (theViewCube,false);
            FlushViewEvents(myContext, myView, Standard_True);
            myInterface->renderGui(myOcctWindow);
        }      
    }
}

// ================================================================
// Function : cleanup
// Purpose  :
// ================================================================
void GlfwOcctView::cleanup()
{

    myInterface->clearImGUI();

    if (!myView.IsNull())
    {
        myView->Remove();
    }
    if (!myOcctWindow.IsNull())
    {
        myOcctWindow->Close();
    }
    glfwTerminate();
}

// ================================================================
// Function : onResize
// Purpose  :
// ================================================================
void GlfwOcctView::onResize(int theWidth, int theHeight)
{

    if (theWidth != 0
        && theHeight != 0
        && !myView.IsNull())
    {
        myView->Window()->DoResize();
        myView->MustBeResized();
        myView->Invalidate();
        myView->Redraw();
    }
}

// ================================================================
// Function : onMouseScroll
// Purpose  :
// ================================================================
void GlfwOcctView::onMouseScroll(double theOffsetX, double theOffsetY)
{
    ImGuiIO& aIO = ImGui::GetIO();
    if (!myView.IsNull() && !aIO.WantCaptureMouse)
    {
        UpdateZoom(Aspect_ScrollDelta(myOcctWindow->CursorPosition(), int(theOffsetY * 8.0)));
    }
}

// ================================================================
// Function : onMouseButton
// Purpose  :
// ================================================================
void GlfwOcctView::onMouseButton(int theButton, int theAction, int theMods)
{
    ImGuiIO& aIO = ImGui::GetIO();
    if (myView.IsNull() || aIO.WantCaptureMouse)
    {
        return;
    }

    const Graphic3d_Vec2i aPos = myOcctWindow->CursorPosition();
    if (theAction == GLFW_PRESS)
    {
        PressMouseButton(aPos, mouseButtonFromGlfw(theButton), keyFlagsFromGlfw(theMods), false);
    }
    else
    {
        ReleaseMouseButton(aPos, mouseButtonFromGlfw(theButton), keyFlagsFromGlfw(theMods), false);
    }
}

// ================================================================
// Function : onMouseMove
// Purpose  :
// ================================================================
void GlfwOcctView::onMouseMove(int thePosX, int thePosY)
{
    if (myView.IsNull())
    {
        return;
    }

    ImGuiIO& aIO = ImGui::GetIO();
    if (aIO.WantCaptureMouse)
    {
        myView->Redraw();
    }
    else
    {
        const Graphic3d_Vec2i aNewPos(thePosX, thePosY);
        UpdateMousePosition(aNewPos, PressedMouseButtons(), LastMouseFlags(), Standard_False);
    }
}
