#pragma once
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_InteractiveObject.hxx>

class GlfwOcctView;
class ModelingCascade
{
public:
    ModelingCascade();
    ModelingCascade(const ModelingCascade&) = default;
    ModelingCascade(ModelingCascade&&) = default;
    ModelingCascade& operator = (const ModelingCascade&) = default;
    ModelingCascade& operator = (ModelingCascade&&) = default;
    virtual ~ModelingCascade() = default;

    bool CreateHelix(GlfwOcctView *obj, int k ,  Handle(AIS_Shape) ais_shape[]);
    bool Lab2(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab3(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab4(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab5(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab6(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab7(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab8(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[], float radius = 15, int Plheignt = 10);
    bool Lab9(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[]);
    bool Lab10(GlfwOcctView *obj, Handle(AIS_Shape) ais_shape[], float radius = 8);
    bool ExportStep (const TCollection_AsciiString& theFileName, GlfwOcctView *obj);
    bool ColorFaces(GlfwOcctView *obj);
    bool TopoInfo(GlfwOcctView *obj, int num[]);

    bool ImportStep(const Standard_CString& theFileName, GlfwOcctView *obj);
    bool CreateConus(GlfwOcctView *obj, int &koef, Handle(AIS_Shape) &aCone);
    bool CreateSome3D(GlfwOcctView *obj) noexcept;
    bool CreateStraightLine(GlfwOcctView *obj) noexcept;


private:
   // GlfwOcctView *objGlfwOcctView;
};


