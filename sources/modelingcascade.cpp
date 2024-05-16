#include "modelingcascade.h"
#include "GlfwOcctView.h"
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>



ModelingCascade::ModelingCascade()
{

}
bool ModelingCascade::CreateSome3D(GlfwOcctView *obj) noexcept
{
    obj->getContext()->RemoveAll(true);
    obj->getContext()->UpdateCurrentViewer();
    gp_Ax2 anAxis;
    anAxis.SetLocation (gp_Pnt (0.0, 0.0, 0.0));
    Handle(AIS_Shape) aBox = new AIS_Shape (BRepPrimAPI_MakeBox (anAxis, 50, 50, 50).Shape());
    obj->getContext()->Display (aBox, AIS_Shaded, 0, false);
    anAxis.SetLocation (gp_Pnt (25.0, 125.0, 0.0));

    anAxis.SetLocation (gp_Pnt (100, 100.0, 0.0));
    Handle(AIS_Shape) aCylinder = new AIS_Shape (BRepPrimAPI_MakeCylinder(anAxis, 25, 50, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aCylinder, AIS_Shaded, 0, false);

    anAxis.SetLocation (gp_Pnt (150, 50.0, 0.0));
    Handle(AIS_Shape) aTorus = new AIS_Shape (BRepPrimAPI_MakeTorus(anAxis, 30, 15, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aTorus, AIS_Shaded, 0, false);

    anAxis.SetLocation (gp_Pnt (150, 150.0, 0.0));
    Handle(AIS_Shape) aSphere= new AIS_Shape (BRepPrimAPI_MakeSphere(anAxis, 30, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aSphere, AIS_Shaded, 0, false);
    return true;
}
#include <Geom_Line.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
bool ModelingCascade::CreateStraightLine(GlfwOcctView *obj) noexcept
{
    // Define the start and end points of the line
    gp_Pnt startPoint(0., 0., 0.);
    gp_Pnt endPoint(1., 1., 0.);

    // Create a direction vector for the line
    gp_Dir direction(gp_Vec(startPoint, endPoint));

    // Create the line using the start point and direction
    Handle(Geom_Line) line = new Geom_Line(startPoint, direction);

    //!Get points the coordinates of some points on the line
    //gp_Pnt point1 = line->Value(0); // Start point
    //gp_Pnt point2 = line->Value(0.5); // Midpoint
    //gp_Pnt point3 = line->Value(1); // End point

    // Create an AIS_Shape object and initialize it with the Geom_Line
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(line);
    Handle(AIS_Shape) shape = new AIS_Shape(edge);
    obj->getContext()->Display (shape, AIS_Shaded, 0, true);

   return true;
}

bool ModelingCascade::CreateConus(GlfwOcctView *obj, int &koef , Handle(AIS_Shape) &aCone)
{
    gp_Ax2 anAxis;
    anAxis.SetLocation (gp_Pnt (25.0, 125.0, 0.0));
    aCone = new AIS_Shape (BRepPrimAPI_MakeCone (anAxis, 25, 0, 10*koef).Shape());
    return true;
}

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <math.h>
bool ModelingCascade::Lab2(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    gp_Pnt pnt1( 0.0,0.0,0.0 );
    TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex( pnt1 );
    Handle(AIS_Shape) aV1 = new  AIS_Shape(V1);
    aV1->SetColor(Quantity_NOC_ORANGE);

    gp_Pnt pnt2( 0.0,100.0,0.0 );
    TopoDS_Vertex V2 = BRepBuilderAPI_MakeVertex( pnt2 );
    Handle(AIS_Shape) aV2 = new  AIS_Shape(V2);

    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(pnt1,pnt2);
    Handle(AIS_Shape) theLine = new  AIS_Shape(edge);

    const Standard_Real r=45 ;
    gp_Trsf myTrsf;
    myTrsf.SetRotation(gp::OX(), r * M_PI /180);
    gp_Pnt rotPoint = pnt2.Transformed(myTrsf);
    TopoDS_Vertex rotPointVert = BRepBuilderAPI_MakeVertex( rotPoint );
    Handle(AIS_Shape) aV3 = new  AIS_Shape(rotPointVert);
    aV3->SetColor(Quantity_NOC_PALEGREEN3);

    TopoDS_Edge edgeRot = BRepBuilderAPI_MakeEdge(pnt1,rotPoint);
    Handle(AIS_Shape) theLineRot = new  AIS_Shape(edgeRot);
    theLineRot->SetColor(Quantity_NOC_GRAY22);

    ais_shape[0] = aV1;
    ais_shape[1] = aV2;
    ais_shape[2] = theLine;
    ais_shape[3] = aV3;
    ais_shape[4] = theLineRot;
    return true;
}

bool ModelingCascade::Lab3(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
  return 1;
}
#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
bool ModelingCascade::Lab4(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    const double a = 40.0;
    const double b = 0.0;
    const int N = 1000;
    const double angleIncrement = 8 * M_PI / N;

    std::vector<gp_Pnt> points;

    for (int i = 0; i < N; ++i) {
        double angle = i * angleIncrement;
        double radius = a - (a * i / N);
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        double z = b * i;
        points.push_back(gp_Pnt(x, y, z));
    }

    TColgp_Array1OfPnt array(1, N);
    for (int i = 0; i < N; ++i) {
        array(i + 1) = points[i];
    }

    const Standard_Integer degree = 3;

    Handle(Geom_BSplineCurve) curve_bspline = GeomAPI_PointsToBSpline(array).Curve();
    TopoDS_Edge myEdge1 = BRepBuilderAPI_MakeEdge(curve_bspline);

    Handle(AIS_Shape) aisEdge1 = new AIS_Shape(myEdge1);
    aisEdge1->SetWidth(3.0);
    aisEdge1->SetColor(Quantity_NOC_AQUAMARINE1);
    ais_shape[0] = aisEdge1;
    return 1;
}
#include <GeomConvert.hxx>
#include <Geom_BezierCurve.hxx>
bool ModelingCascade::Lab5(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    int x1 = 20, y1 = 30;
    int x2 = 80, y2 = 300;
    int x3 = 140, y3 = 30;
    TColgp_Array1OfPnt dots (1,100);
    for(Standard_Real t=0, i = 1; t<=1; t+=0.01, i++)
    {
        Standard_Real x = pow((1-t),2) * x1 + 2*(1-t) * t * x2 + pow(t,2) * x3;
        Standard_Real y = pow((1-t),2) * y1 + 2*(1-t) * t * y2 + pow(t,2) * y3;
        gp_Pnt pnt(x,y,0);
        dots.SetValue(i,pnt);
    }
    Handle(Geom_BSplineCurve) curve_bspline = GeomAPI_PointsToBSpline(dots).Curve();
    TopoDS_Edge myEdge = BRepBuilderAPI_MakeEdge(curve_bspline);
    Handle(AIS_Shape) aCurve = new AIS_Shape(myEdge);

    TColgp_Array1OfPnt array(1,3);
    gp_Pnt myPoint1(20,30,40);
    gp_Pnt myPoint2(80,300,40);
    gp_Pnt myPoint3(140,30,40);
    array.SetValue(1,myPoint1);
    array.SetValue(2,myPoint2);
    array.SetValue(3,myPoint3);
    Handle(Geom_BezierCurve) curve_bz = new Geom_BezierCurve(array);
    Handle(Geom_BSplineCurve) e1_geom = GeomConvert::CurveToBSplineCurve(curve_bz);
    TopoDS_Edge myEdge1 = BRepBuilderAPI_MakeEdge(e1_geom);
    Handle(AIS_Shape) aisEdge1=new AIS_Shape(myEdge1);
    aisEdge1->SetColor(Quantity_NOC_WHITESMOKE);
    ais_shape[0] = aCurve;
    ais_shape[1] = aisEdge1;
     return 1;
}

#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineSurface.hxx>

bool ModelingCascade::Lab6(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    int arraySize=3;
    TColgp_Array2OfPnt myStucture(0,arraySize,0,arraySize);
    srand(time(NULL));
    for(int i=0; i<=arraySize; i++)
    {
        for(int j=0; j<=arraySize; j++)
        {
            int z=10+rand()%(100-1);
            myStucture.SetValue(j,i,gp_Pnt(i+10*pow(i,2),j+20*pow(j,2),z));
        }
    }
    Handle (Geom_Surface) myGSurface = new Geom_BezierSurface(myStucture);
    TopoDS_Face myFace = BRepBuilderAPI_MakeFace(myGSurface,0.01);
    Handle(AIS_Shape) aisFace=new AIS_Shape(myFace);
    aisFace->SetColor(Quantity_NOC_PINK1);
    aisFace->SetDisplayMode(AIS_Shaded);
    ais_shape[0] = aisFace;
    return 1;
}

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
bool ModelingCascade::Lab7(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    TopoDS_Shape cube = BRepPrimAPI_MakeBox(gp_Pnt(0.0, 0.0, 0.0), gp_Pnt(150, 100, 150)).Shape();
    Handle(AIS_Shape) aCube=new AIS_Shape(cube);
    aCube->SetMaterial( Graphic3d_NOM_CHROME);
    aCube->SetDisplayMode(AIS_Shaded);
    aCube->SetColor(Quantity_NOC_ALICEBLUE);

    gp_Ax2 anAxis(gp_Pnt(0,150,0),gp_Dir(0,0,1));
    TopoDS_Shape torus = BRepPrimAPI_MakeTorus(anAxis,150, 5, (180 * M_PI /180));
    Handle(AIS_Shape) aTorus=new AIS_Shape(torus);
    aTorus->SetMaterial( Graphic3d_NOM_CHROME);
    aTorus->SetDisplayMode(AIS_Shaded);
    aTorus->SetColor(Quantity_NOC_ALICEBLUE);

    ais_shape[0] = aCube;
    ais_shape[1] = aTorus;
    return 1;
}
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
bool ModelingCascade::Lab8(GlfwOcctView *obj, opencascade::handle<AIS_Shape> ais_shape[], float radius, int Plheignt)
{
    TopoDS_Shape cube = BRepPrimAPI_MakeBox(gp_Pnt(-25, -25, 0.0), gp_Pnt(25, 25, Plheignt)).Shape();

    TopoDS_Shape cyl = BRepPrimAPI_MakeCylinder
                       (gp_Ax2(gp_Pnt(0, 0, Plheignt), gp_Dir(0, 0, 1)), 12.5, 40).Shape();
    TopoDS_Shape cyl_2 = BRepPrimAPI_MakeCylinder
                         (gp_Ax2(gp_Pnt(0, 0, Plheignt), gp_Dir(0, 0, 1)), radius/2, 40).Shape();
    TopoDS_Shape ShapeCut_1 = BRepAlgoAPI_Cut(cyl, cyl_2);
    TopoDS_Shape ShapeFuse_1 = BRepAlgoAPI_Fuse(cube, ShapeCut_1);
    Handle(AIS_Shape) platform = new AIS_Shape(ShapeFuse_1);
    platform->SetMaterial( Graphic3d_NOM_CHROME);
    platform->SetDisplayMode(AIS_Shaded);
    platform->SetColor(Quantity_NOC_ALICEBLUE);

    TopoDS_Shape cyl_3 = BRepPrimAPI_MakeCylinder
                         (gp_Ax2(gp_Pnt(100, 100, 0), gp_Dir(0, 0, 1)), 15, 50).Shape();
    TopoDS_Shape cube_2 = BRepPrimAPI_MakeBox(gp_Pnt(75, 75, 50), gp_Pnt(125, 125, 100)).Shape();
    TopoDS_Shape cube_3 = BRepPrimAPI_MakeBox(gp_Pnt(77.5, 77.5, 55), gp_Pnt(122.5, 122.5, 100)).Shape();
    TopoDS_Shape ShapeCut_2 = BRepAlgoAPI_Cut(cube_2, cube_3);
    TopoDS_Shape ShapeFuse_2 = BRepAlgoAPI_Fuse(cyl_3, ShapeCut_2);
    Handle(AIS_Shape) stoika = new AIS_Shape(ShapeFuse_2);
    stoika->SetMaterial( Graphic3d_NOM_CHROME);
    stoika->SetDisplayMode(AIS_Shaded);
    stoika->SetColor(Quantity_NOC_ALICEBLUE);
    ais_shape[0] = platform;
    ais_shape[1] = stoika;
    return 1;
}
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopoDS.hxx>
bool ModelingCascade::Lab9(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[])
{
    Standard_Real rad = 10;
    TopoDS_Shape cube = BRepPrimAPI_MakeBox(gp_Pnt(-rad, -rad, 0.0), gp_Pnt(50, 40, 5)).Shape();

    TopTools_IndexedMapOfShape edge; // массив ребер
    TopExp::MapShapes(cube, TopAbs_EDGE, edge);
    BRepFilletAPI_MakeFillet aFillet1(cube);
    aFillet1.Add(10, TopoDS::Edge(edge.FindKey(1)));

    TopoDS_Shape cyl = BRepPrimAPI_MakeCylinder
                       (gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), rad, 8).Shape();

    TopTools_IndexedMapOfShape edgeCyl; // массив ребер
    TopExp::MapShapes(cyl, TopAbs_EDGE, edgeCyl);
    BRepFilletAPI_MakeChamfer aChamferCyl(cyl);
    aChamferCyl.Add(0.5, TopoDS::Edge(edgeCyl.FindKey(1)));

    TopoDS_Shape ShapeFuse_1 = BRepAlgoAPI_Fuse(aFillet1, aChamferCyl);

    TopoDS_Shape cube2 = BRepPrimAPI_MakeBox(gp_Pnt(50, 40, 0.0), gp_Pnt(40, -rad, 30)).Shape();

    TopTools_IndexedMapOfShape edge1; // массив ребер
    TopExp::MapShapes(cube2, TopAbs_EDGE, edge1);

    TopTools_IndexedMapOfShape face1; // массив граней
    TopExp::MapShapes(cube2 , TopAbs_FACE, face1);

    BRepFilletAPI_MakeChamfer aChamfer(cube2);
    aChamfer.Add(5, TopoDS::Edge(edge1.FindKey(10)));
    TopoDS_Shape ShapeFuse_2 = BRepAlgoAPI_Fuse(ShapeFuse_1, aChamfer);

    TopoDS_Shape cube3 = BRepPrimAPI_MakeBox(gp_Pnt(50, 40, 0.0), gp_Pnt(-rad, 30, 30)).Shape();
    TopTools_IndexedMapOfShape edge2; // массив ребер
    TopExp::MapShapes(cube3, TopAbs_EDGE, edge2);

    BRepFilletAPI_MakeChamfer aChamfer1(cube3);
    aChamfer1.Add(5, TopoDS::Edge(edge2.FindKey(2)));
    TopoDS_Shape ShapeFuse_3 = BRepAlgoAPI_Fuse(ShapeFuse_2, aChamfer1);

    TopoDS_Shape cube4 = BRepPrimAPI_MakeBox(gp_Pnt(15, 40, 15), gp_Pnt(25, 30, 30)).Shape();

    TopTools_IndexedMapOfShape edge4; // массив ребер
    TopExp::MapShapes(cube4, TopAbs_EDGE, edge4);
    BRepFilletAPI_MakeFillet aFillet(cube4);
    aFillet.Add(2, TopoDS::Edge(edge4.FindKey(4)));
    aFillet.Add(2, TopoDS::Edge(edge4.FindKey(8)));
    TopoDS_Shape ShapeCut_4 = BRepAlgoAPI_Cut(ShapeFuse_3, aFillet);

    TopoDS_Shape cyl_2 = BRepPrimAPI_MakeCylinder
                         (gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 6, 8).Shape();
    TopoDS_Shape ShapeCut_5 = BRepAlgoAPI_Cut(ShapeCut_4, cyl_2);

    Handle(AIS_Shape) result = new AIS_Shape(ShapeCut_5);
    result->SetMaterial( Graphic3d_NOM_CHROME);
    result->SetDisplayMode(AIS_Shaded);
    result->SetColor(Quantity_NOC_ALICEBLUE);
    ais_shape[0] = result;
    return 1;
}
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
bool ModelingCascade::Lab10(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[], float radius)
{
    TopoDS_Shape cube1 = BRepPrimAPI_MakeBox(gp_Pnt(100, 70, 0.0), gp_Pnt(0, 0, 12)).Shape();
    TopTools_IndexedMapOfShape edge1; // массив ребер
    TopExp::MapShapes(cube1, TopAbs_EDGE, edge1);
    BRepFilletAPI_MakeFillet aFillet1(cube1);
    aFillet1.Add(10, TopoDS::Edge(edge1.FindKey(7)));
    aFillet1.Add(10, TopoDS::Edge(edge1.FindKey(3)));

    TopoDS_Shape cyl2 = BRepPrimAPI_MakeCylinder
                        (gp_Ax2(gp_Pnt(85, 50, 0), gp_Dir(0, 0, 1)), radius, 12).Shape();
    TopoDS_Shape cyl3 = BRepPrimAPI_MakeCylinder
                        (gp_Ax2(gp_Pnt(15, 50, 0), gp_Dir(0, 0, 1)), radius, 12).Shape();
    TopoDS_Shape ShapeCutCube1 = BRepAlgoAPI_Cut(aFillet1, cyl2);
    ShapeCutCube1 = BRepAlgoAPI_Cut(ShapeCutCube1, cyl3);

    gp_Pnt pnt8(35, 0, 56);
    gp_Pnt pnt9(65, 0, 56);
    gp_Pnt pnt10(100, 0, 12);
    gp_Pnt pnt11(0, 0, 12);
    TopoDS_Edge aEdge8 = BRepBuilderAPI_MakeEdge(pnt8, pnt9);
    TopoDS_Edge aEdge9 = BRepBuilderAPI_MakeEdge(pnt10, pnt11);
    TopoDS_Edge aEdge10 = BRepBuilderAPI_MakeEdge(pnt8, pnt11);
    TopoDS_Edge aEdge11 = BRepBuilderAPI_MakeEdge(pnt9, pnt10);
    BRepBuilderAPI_MakeWire makeW2;
    makeW2.Add(aEdge8);
    makeW2.Add(aEdge9);
    makeW2.Add(aEdge10);
    makeW2.Add(aEdge11);
    TopoDS_Wire Wc2 = makeW2.Wire();
    TopoDS_Face F2 = BRepBuilderAPI_MakeFace(Wc2);
    gp_Vec move2(gp_Dir(0, 1, 0));
    move2 *= 10;
    TopoDS_Shape trapecia = BRepPrimAPI_MakePrism(F2, move2);

    TopoDS_Shape ShapeFuseCube1 = BRepAlgoAPI_Fuse(ShapeCutCube1, trapecia);

    TopoDS_Shape cyl = BRepPrimAPI_MakeCylinder
                       (gp_Ax2(gp_Pnt(50, 0, 56), gp_Dir(0, 1, 0)), 15, 50).Shape();

    TopoDS_Shape cyl1 = BRepPrimAPI_MakeCylinder
                        (gp_Ax2(gp_Pnt(50, 0, 56), gp_Dir(0, 1, 0)), 8, 50).Shape();

    TopoDS_Shape ShapeCutCyl1 = BRepAlgoAPI_Cut(ShapeFuseCube1, cyl);
    TopoDS_Shape ShapeCutCyl2 = BRepAlgoAPI_Cut(cyl, cyl1);
    TopoDS_Shape ShapeFuseCyl1 = BRepAlgoAPI_Fuse(ShapeCutCyl1, ShapeCutCyl2);

    gp_Pnt pnt1(55, 55, 10);
    gp_Pnt pnt2(45, 55, 10);
    gp_Pnt pnt3(55, 50, 10);
    gp_Pnt pnt4(45, 50, 10);
    TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(pnt1, pnt2);
    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(pnt2, pnt4);
    TopoDS_Edge aEdge3 = BRepBuilderAPI_MakeEdge(pnt3, pnt4);
    TopoDS_Edge aEdge4 = BRepBuilderAPI_MakeEdge(pnt3, pnt1);
    BRepBuilderAPI_MakeWire makeW;
    makeW.Add(aEdge1);
    makeW.Add(aEdge2);
    makeW.Add(aEdge3);
    makeW.Add(aEdge4);
    TopoDS_Wire Wc = makeW.Wire();
    TopoDS_Face F = BRepBuilderAPI_MakeFace(Wc);
    gp_Vec move(gp_Dir(0, -0.5, 1));
    move *= 37;
    TopoDS_Shape cube2 = BRepPrimAPI_MakePrism(F, move);

    TopoDS_Shape ShapeFuseCyl2 = BRepAlgoAPI_Fuse(ShapeFuseCyl1, cube2);

    TopoDS_Shape cube3 = BRepPrimAPI_MakeBox(gp_Pnt(52.5, 55, 10), gp_Pnt(47.5, 0, 41.25)).Shape();
    gp_Pnt pnt5(55, 55, 41.5);
    gp_Pnt pnt6(55, 37.5, 41.5);
    gp_Pnt pnt7(55, 55, 10);
    TopoDS_Edge aEdge5 = BRepBuilderAPI_MakeEdge(pnt5, pnt6);
    TopoDS_Edge aEdge6 = BRepBuilderAPI_MakeEdge(pnt6, pnt7);
    TopoDS_Edge aEdge7 = BRepBuilderAPI_MakeEdge(pnt7, pnt5);
    BRepBuilderAPI_MakeWire makeW1;
    makeW1.Add(aEdge5);
    makeW1.Add(aEdge6);
    makeW1.Add(aEdge7);
    TopoDS_Wire Wc1 = makeW1.Wire();
    TopoDS_Face F1 = BRepBuilderAPI_MakeFace(Wc1);
    gp_Vec move1(gp_Dir(-1, 0, 0));
    move1 *= 10;
    TopoDS_Shape cutTrinagle = BRepPrimAPI_MakePrism(F1, move1);
    TopoDS_Shape ShapeCutTriangle = BRepAlgoAPI_Cut(cube3, cutTrinagle);

    TopoDS_Shape ShapeFuseCyl3 = BRepAlgoAPI_Fuse(ShapeFuseCyl2, ShapeCutTriangle);

    TopoDS_Shape cyl5 = BRepPrimAPI_MakeCylinder
                        (gp_Ax2(gp_Pnt(50, 15, 71), gp_Dir(0, 0, -1)), 3, 10).Shape();

    TopoDS_Shape ShapeFuseCyl4 = BRepAlgoAPI_Cut(ShapeFuseCyl3, cyl5);

    TopTools_IndexedMapOfShape resultEdge; // массив ребер
    TopExp::MapShapes(ShapeFuseCyl4, TopAbs_EDGE, resultEdge);
    BRepFilletAPI_MakeFillet resFillet(ShapeFuseCyl4);
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(10)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(11)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(12)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(13)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(14)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(15)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(16)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(17)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(21)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(23)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(24)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(25)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(26)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(27)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(28)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(29)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(30)));
    resFillet.Add(2, TopoDS::Edge(resultEdge.FindKey(31)));
    Handle(AIS_Shape) result = new AIS_Shape(resFillet);
    result->SetMaterial( Graphic3d_NOM_CHROME);
    result->SetDisplayMode(AIS_Shaded);
    ais_shape[0] = result;
    return 1;
}
#include <STEPControl_StepModelType.hxx>
#include <STEPControl_Writer.hxx>
bool ModelingCascade::ExportStep (const TCollection_AsciiString& theFileName, GlfwOcctView *obj)
{
    STEPControl_StepModelType aType = STEPControl_AsIs;
    STEPControl_Writer        aWriter;
    for (obj->getContext()->InitSelected(); obj->getContext()->MoreSelected(); obj->getContext()->NextSelected())
    {
        Handle(AIS_Shape) anIS = Handle(AIS_Shape)::DownCast (obj->getContext()->SelectedInteractive());
        if (anIS.IsNull())
        {
            return false;
        }
        TopoDS_Shape aShape = anIS->Shape();
        if (aWriter.Transfer (aShape, aType) != IFSelect_RetDone)
        {
            return false;
        }
    }
    return aWriter.Write (theFileName.ToCString()) == IFSelect_RetDone;
}
#include <STEPControl_Reader.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <BRepTools.hxx>
bool ModelingCascade::ImportStep(const Standard_CString &theFileName, GlfwOcctView *obj)
{
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(theFileName);
    if (status != IFSelect_RetDone) {
        return false;

    }
    else {
        aReader.NbRootsForTransfer();
        aReader.TransferRoots();
        TopoDS_Shape shape = aReader.OneShape();
        Handle(AIS_Shape) result = new  AIS_Shape(shape);
        result->SetMaterial( Graphic3d_NOM_CHROME);
        obj->getContext()->Display(result, AIS_Shaded, 0, false);
        return 1;
    }
}
#include <TopExp_Explorer.hxx>
bool ModelingCascade::ColorFaces(GlfwOcctView *obj)
{
    for (obj->getContext()->InitSelected(); obj->getContext()->MoreSelected(); obj->getContext()->NextSelected())
    {
        Handle(AIS_Shape) anIS = Handle(AIS_Shape)::DownCast(obj->getContext()->SelectedInteractive());
        if (anIS.IsNull())
        {
            return false;
        }
        TopoDS_Shape S = anIS->Shape();

        for (TopExp_Explorer ex(S, TopAbs_FACE); ex.More(); ex.Next())
        {
            TopoDS_Shape myTopoDS = ex.Current();
            BRepAdaptor_Surface surface(TopoDS::Face(myTopoDS));
            if (surface.GetType() == GeomAbs_Plane) // Проверяем, является ли грань плоской
            {
                Handle(AIS_Shape) myShape = new AIS_Shape(myTopoDS);
                myShape->SetColor(Quantity_NOC_RED);
                myShape->SetDisplayMode(AIS_Shaded);
                obj->getContext()->Display(myShape, AIS_Shaded, 0, false);
            }
        }
    }
}
#include <set>
bool ModelingCascade::TopoInfo(GlfwOcctView *obj, int num[])
{
    int totalVertices = 0;
    int totalEdges = 0;
    int totalFaces = 0;
    for (obj->getContext()->InitSelected(); obj->getContext()->MoreSelected(); obj->getContext()->NextSelected())
    {
        Handle(AIS_Shape) anIS = Handle(AIS_Shape)::DownCast(obj->getContext()->SelectedInteractive());
        if (anIS.IsNull())
        {
            return false;
        }
        TopoDS_Shape S = anIS->Shape();


          std::set<TopoDS_Vertex> vertices;
        // Подсчет количества точек, ребер и граней

        TopExp_Explorer explorer(S, TopAbs_VERTEX);
        // for (; explorer.More(); explorer.Next())
        // {
        //     // TopoDS_Vertex vertex = TopoDS::Vertex(explorer.Current());
        //     // vertices.insert(vertex);
        // }
        // totalVertices = vertices.size();
        TopTools_IndexedMapOfShape v;
        TopExp::MapShapes(S , TopAbs_VERTEX, v);
        totalVertices = v.Size();

        TopTools_IndexedMapOfShape m;
        TopExp::MapShapes(S , TopAbs_EDGE, m);
        totalEdges = m.Size();

        explorer.Init(S, TopAbs_FACE);
        for (; explorer.More(); explorer.Next())
        {
            totalFaces++;
        }
    }
    num[0] = totalFaces;
    num[1] = totalEdges;
    num[2] = totalVertices;
    return 1;
}
bool ModelingCascade::CreateHelix(GlfwOcctView *obj, int k ,  Handle(AIS_Shape) ais_shape[])
{
     const double R = 50.0;
     const double H = 500;
     const int N = 100;
    TColgp_Array1OfPnt points (0,N*k);
     for(int j = 1; j<=k; j++){
        for (int i = 0; i <= N; i++) {
            double t = 2 * M_PI * i / N;
            double x = R * cos(t);
            double y = R * sin(t);
            double z = H * t / N + (H * 2 * M_PI / N * (j-1));
            gp_Pnt pnt(x, y, z);
            points.SetValue(i+(j-1)*N, pnt);
        }
    }
     // Standard_Real myDistance = points[0].Distance(points[200]);
     Handle(Geom_BSplineCurve) e1_geom = GeomAPI_PointsToBSpline(points).Curve();
     TopoDS_Edge myEdge1 = BRepBuilderAPI_MakeEdge(e1_geom);
     Handle(AIS_Shape) aisEdge1 = new AIS_Shape(myEdge1);
     ais_shape[0] = aisEdge1;
    return 1;
}

