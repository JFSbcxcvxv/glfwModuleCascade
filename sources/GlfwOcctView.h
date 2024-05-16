#pragma once

#include "GlfwOcctWindow.h"
#include "interfaceimgui.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>

#include <memory>

//! Sample class creating 3D Viewer within GLFW window.
class GlfwOcctView : protected AIS_ViewController
{
public:
    //! Default constructor.
    GlfwOcctView();

    //! Destructor.
    ~GlfwOcctView();

    //! Main application entry point.
    void run();

    Handle(AIS_InteractiveContext) getContext() const noexcept
    {
        return myContext;
    }

    Handle(V3d_View) getView() const noexcept
    {
       return myView;
    }


private:

    //! Create GLFW window.
    void initWindow(int theWidth, int theHeight, const char* theTitle);

    //! Create 3D Viewer.
    void initViewer();


    //! Fill 3D Viewer with a DEMO items.
    void initDemoScene();

    //! Application event loop.
    void mainloop();

    //! Clean up before .
    void cleanup();

    //! @name GLWF callbacks
private:
    //! Window resize event.
    void onResize(int theWidth, int theHeight);

    //! Mouse scroll event.
    void onMouseScroll(double theOffsetX, double theOffsetY);

    //! Mouse click event.
    void onMouseButton(int theButton, int theAction, int theMods);

    //! Mouse move event.
    void onMouseMove(int thePosX, int thePosY);

    //! @name GLWF callbacks (static functions)
private:

    //! GLFW callback redirecting messages into Message::DefaultMessenger().
    static void errorCallback(int theError, const char* theDescription);

    //! Wrapper for glfwGetWindowUserPointer() returning this class instance.
    static GlfwOcctView* toView(GLFWwindow* theWin);

    //! Window resize callback.
    static void onResizeCallback(GLFWwindow* theWin, int theWidth, int theHeight)
    {
        toView(theWin)->onResize(theWidth, theHeight);
    }

    //! Frame-buffer resize callback.
    static void onFBResizeCallback(GLFWwindow* theWin, int theWidth, int theHeight)
    {
        toView(theWin)->onResize(theWidth, theHeight);
    }

    //! Mouse scroll callback.
    static void onMouseScrollCallback(GLFWwindow* theWin, double theOffsetX, double theOffsetY)
    {
        toView(theWin)->onMouseScroll(theOffsetX, theOffsetY);
    }

    //! Mouse click callback.
    static void onMouseButtonCallback(GLFWwindow* theWin, int theButton, int theAction, int theMods)
    {
        toView(theWin)->onMouseButton(theButton, theAction, theMods);
    }

    //! Mouse move callback.
    static void onMouseMoveCallback(GLFWwindow* theWin, double thePosX, double thePosY)
    {
        toView(theWin)->onMouseMove((int)thePosX, (int)thePosY);
    }

private:

    //InterfaceCAD *myInterface;
    std::unique_ptr<InterfaceCAD> myInterface;
    Handle(GlfwOcctWindow) myOcctWindow;
    Handle(V3d_View) myView;
    Handle(AIS_InteractiveContext) myContext;
    Handle(AIS_ViewCube) theViewCube;
    Handle(AIS_Shape) aCone;

};


