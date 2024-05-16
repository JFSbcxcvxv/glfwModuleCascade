#include "GlfwOcctView.h"
#include "interfaceimgui.h"
#include "modelingcascade.h"

#include <string>
#include "GLFW/glfw3.h"
#include "spdlog/include/spdlog/spdlog.h"
#include <filesystem>


#include "imgui/imgui.h"
#include "L2DFileDialog.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


void InterfaceCAD::initGui(Handle(GlfwOcctWindow) &objGLFW)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& aIO = ImGui::GetIO();
    // aIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //how to get current directory
    std::string path = std::filesystem::current_path().string();
    spdlog::info("current path: {0}", path);
//Window path
#ifdef _WIN32
    std::string s = "build\\sources";
#endif
//Linux path
#ifdef linux
    std::string s = "build/sources";
#endif

    std::string::size_type i = path.find(s);
    if (i != std::string::npos)
        path.erase(i, s.length());
//Window path
#ifdef _WIN32
    path.append("ttf\\Roboto-Medium.ttf");
#endif
//Linux path
#ifdef linux
      path.append("ttf/Nevrouz_M.ttf");
#endif
    //necessary path for the font
    spdlog::info("necessary path for the font: {0}", path);
    //add user font in form
    // aIO.Fonts ->AddFontFromFileTTF(path.c_str(), 18, NULL,
    //                               aIO.Fonts->GetGlyphRangesCyrillic());
    aIO.Fonts ->AddFontFromFileTTF("D:\\GemMode\\glfwModuleCascade\\ttf\\Roboto-Medium.ttf", 18, NULL,
                                  aIO.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplGlfw_InitForOpenGL(objGLFW->getGlfwWindow(), Standard_True);
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style.
    //ImGui::StyleColorsClassic();
}
bool show_dialog_save = false;
bool show_dialog_open = false;
bool show_dialog_topinfo = false;
void InterfaceCAD:: menuToolBar(Handle(GlfwOcctWindow) &objGLFW)
{
    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Clearing all in a window"))
            {
                spdlog::info("Welcome to spdlog!");
                objView->getContext()->RemoveAll(true);
                objView->getContext()->UpdateCurrentViewer();

            }
            if(ImGui::MenuItem("Maximum Size"))
            {
                objView->getView()->FitAll();
                objView->getView()->Redraw();
            }
            if(ImGui::MenuItem("Сохранить как"))
            {
                show_dialog_save = true;
            }
            if(ImGui::MenuItem("Открыть"))
            {
                show_dialog_open = true;
            }
            if(ImGui::MenuItem("Exit"))
            {
                glfwSetWindowShouldClose(objGLFW->getGlfwWindow(), GL_TRUE);

            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Лабораторные"))
        {
            if(ImGui::MenuItem("Лабораторная работа 1"))
            {
                spdlog::info("Project created");
            }
            else if(ImGui::MenuItem("Лабораторная работа 2"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[5];
                objModelingCascade->Lab2(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }

            }
            else if(ImGui::MenuItem("Лабораторная работа 3"))
            {

            }
            else if (ImGui::MenuItem("Лабораторная работа 4"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[1];
                objModelingCascade->Lab4(objView, ais_shape);
                objView->getContext()->Display (ais_shape[0], AIS_Shaded, 0, false);

            }
            else if(ImGui::MenuItem("Лабораторная работа 5"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[2];
                objModelingCascade->Lab5(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }

            }
            else if(ImGui::MenuItem("Лабораторная работа 6"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[1];
                objModelingCascade->Lab6(objView, ais_shape);
                objView->getContext()->Display (ais_shape[0], AIS_Shaded, 0, false);
            }
            else if(ImGui::MenuItem("Лабораторная работа 7"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[2];
                objModelingCascade->Lab7(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }
            }
            else if(ImGui::MenuItem("Лабораторная работа 8"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[2];
                objModelingCascade->Lab8(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }
            }
            else if(ImGui::MenuItem("Лабораторная работа 9"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[1];
                objModelingCascade->Lab9(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }
            }
            else if(ImGui::MenuItem("Лабораторная работа 10"))
            {
                objView->getContext()->RemoveAll(true);
                // objView->getContext()->UpdateCurrentViewer();
                Handle(AIS_Shape)  ais_shape[1];
                objModelingCascade->Lab10(objView, ais_shape);
                for (int i = 0; i < std::size(ais_shape); i++) {
                    objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Samples"))
        {
            if(ImGui::MenuItem("Demo 3D Primitives"))
            {
                if (objModelingCascade->CreateSome3D(objView))
                {
                    spdlog::info("The 3D objects have been successfully created: code 0x{0}", 0);
                }
            }
            if(ImGui::MenuItem("Create a line"))
            {
                if (objModelingCascade->CreateStraightLine(objView))
                {
                    spdlog::info("The straight line have been successfully created: code 0x{0}", 0);
                }
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Покраска"))
        {
            objModelingCascade->ColorFaces(objView);
        }
        if (ImGui::MenuItem("Топология"))
        {
            show_dialog_topinfo = true;
        }

        ImGui::EndMainMenuBar();
    }
}
#include <AIS_ViewCube.hxx>
float radius = 0;
float radiusUpora = 8;
int platformHeight = 0;
void InterfaceCAD::renderGui(Handle(GlfwOcctWindow) &objGLFW)
{

    ImGuiIO& aIO = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    menuToolBar(objGLFW);

    //Window #1 -  Hello IMGUI.
    ImGui::Begin("Меню");
    ImGui::Spacing();
    if (ImGui::Button("Платформа",ImVec2(160, 20))) {
          ImGui::OpenPopup("Платформа");
    }
    ImGui::Spacing();
    if (ImGui::Button("Стойка",ImVec2(160, 20))){
        ImGui::OpenPopup("Стойка");
    }
    ImGui::Spacing();
    if (ImGui::Button("Модель упора",ImVec2(160, 20))){
        ImGui::OpenPopup("Модель упора");
    }
    if (ImGui::BeginPopup("Платформа")) {

        ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.1f, 0.2f, 0.3f, 1.0f);
        ImGui::GetStyle().FrameRounding = 5.0f;
        ImGui::GetStyle().GrabRounding = 5.0f;
        ImGui::Text("Внутр. радиус");
        ImGui::Spacing();
        if(ImGui::SliderFloat("R", &radius, 5, 20)){
            objView->getContext()->RemoveAll(true);
            // objView->getContext()->UpdateCurrentViewer();
            Handle(AIS_Shape)  ais_shape[2];
            if(platformHeight!=0){
                objModelingCascade->Lab8(objView, ais_shape,radius,platformHeight);
            }
            else{
                objModelingCascade->Lab8(objView, ais_shape,radius);
            }
            for (int i = 0; i < std::size(ais_shape); i++) {
                objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
            }
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("Высота основы");
        ImGui::Spacing();
        if(ImGui::SliderInt("H", &platformHeight, 5, 20)){
            objView->getContext()->RemoveAll(true);
            // objView->getContext()->UpdateCurrentViewer();
            Handle(AIS_Shape)  ais_shape[2];
            if(radius!=0){
                objModelingCascade->Lab8(objView, ais_shape,radius,platformHeight);
            }
            else{
                objModelingCascade->Lab8(objView, ais_shape,15,platformHeight);
            }
            for (int i = 0; i < std::size(ais_shape); i++) {
                objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
            }
        }
         ImGui::Spacing();
        if (ImGui::Button("Закрыть")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Стойка")) {
        ImGui::Text("отверстия стойки");
        if (ImGui::Button("Закрыть")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Модель упора")) {
        ImGui::Spacing();
        ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.1f, 0.2f, 0.3f, 1.0f);
        ImGui::GetStyle().FrameRounding = 5.0f;
        ImGui::GetStyle().GrabRounding = 5.0f;
        ImGui::Text("Радиус отверстий");
        ImGui::Spacing();
        if(ImGui::SliderFloat("R", &radiusUpora, 2, 13))
        {}
        ImGui::Spacing();
        if (ImGui::Button("Закрыть")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine(200);
        if (ImGui::Button("Принять")) {
            objView->getContext()->RemoveAll(true);
            // objView->getContext()->UpdateCurrentViewer();
            Handle(AIS_Shape)  ais_shape[1];
            objModelingCascade->Lab10(objView, ais_shape, radiusUpora);
            for (int i = 0; i < std::size(ais_shape); i++) {
                objView->getContext()->Display (ais_shape[i], AIS_Shaded, 0, false);
            }
        }


        ImGui::EndPopup();
    }
    // ImGui::Text("Hello ImGui!");
    // ImGui::Text("Hello OpenCASCADE!");
    // ImGui::Button("OK");
    // ImGui::SameLine();
    // ImGui::Button("Cancel");
    ImGui::End();


    int width, height;
    glfwGetWindowSize(objGLFW->getGlfwWindow(), &width, &height);

    //Window #2 - render your GUI
    ImGui::Begin("Спираль");
    ImGui::SetWindowPos(ImVec2(width - 210, 30), ImGuiCond_::ImGuiCond_None);
    ImGui::SetWindowSize(ImVec2(200,200), ImGuiCond_::ImGuiCond_None);
    // if (ImGui::Button("emptyButton")) {
    // }

    ImGui::Text("Витки спирали");
    // int k = 0;
    if (ImGui::SliderInt("Red", &k, 1, 10))
    {
        objView->getContext()->RemoveAll(true);
        objView->getContext()->UpdateCurrentViewer();
        Handle(AIS_Shape)  ais_shape[1];
        objModelingCascade->CreateHelix(objView, k, ais_shape);
        objView->getContext()->Display (ais_shape[0], AIS_Shaded, 0, false);

    }
    ImGui::End();

    if(show_dialog_save)
    {
        bool show_window = true;
        static char* file_dialog_buffer = new char[500];
        static char path1[500] = "";
        static char path2[500] = "";
        static char path3[500] = "";
        ImGui::Begin("Save File", &show_window);
        ImGui::Text("Save in .step format");
        ImGui::Separator();

        // Choose a folder
        ImGui::TextUnformatted("Path");
        ImGui::SetNextItemWidth(380);
        ImGui::InputText("##path1", path1, sizeof(path1));
        ImGui::SameLine();
        if (ImGui::Button("Browse##path1")) {
            file_dialog_buffer = path1;
            FileDialog::file_dialog_open = true;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::SelectFolder;
        }

        // Choose filename
        ImGui::TextUnformatted("Enter filename");
        ImGui::SetNextItemWidth(380);
        ImGui::InputText("##path2", path2, sizeof(path2));
        std::string fullname(path1);
        std::string filename(path2);
        fullname += "\\";
        fullname += filename;
        fullname += ".step";
        strncpy(path3, fullname.c_str(), 500);

        if (FileDialog::file_dialog_open) {
            FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
        }

        if (ImGui::Button("Close"))
        {
            show_window = false;
            show_dialog_save = false;
        }
        ImGui::SameLine(200);
        if (ImGui::Button("Save"))
        {
            objModelingCascade->ExportStep(path3, objView);
            show_window = false;
            show_dialog_save = false;
        }
        ImGui::End();
    }
    if(show_dialog_open)
    {
        bool show_window = true;
        static char* file_dialog_buffer = new char[500];
        static char path1[500] = "";
        ImGui::Begin("Open File", &show_window);
        ImGui::Text("Open .step file");
        ImGui::Separator();

        // Choose a file
        ImGui::TextUnformatted("Path");
        ImGui::SetNextItemWidth(380);
        ImGui::InputText("##path1", path1, sizeof(path1));
        ImGui::SameLine();
        if (ImGui::Button("Browse##path1")) {
            file_dialog_buffer = path1;
            FileDialog::file_dialog_open = true;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
        }
        if (FileDialog::file_dialog_open) {
            FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
        }
        if (ImGui::Button("Close"))
        {
            show_window = false;
            show_dialog_open = false;
        }
        ImGui::SameLine(200);
        if (ImGui::Button("Open"))
        {
            objModelingCascade->ImportStep(path1, objView);
            show_window = false;
            show_dialog_open = false;
        }
         ImGui::End();
    }
    if(show_dialog_topinfo)
    {
        bool show_window = true;
        int num[3];
        objModelingCascade->TopoInfo(objView, num);
        ImGui::Begin("Топлогическая информация модели", &show_window);

        std::string intValueString1 = std::to_string(num[0]);
        std::string intValueString2 = std::to_string(num[1]);
        std::string intValueString3 = std::to_string(num[2]);

        ImGui::Text("Количество граней: %s",intValueString1.c_str() );
        ImGui::Spacing();
        ImGui::Text("Количество ребер: %s",  intValueString2.c_str());
        ImGui::Spacing();
        ImGui::Text("Количество вершин: %s",  intValueString3.c_str());
        ImGui::Spacing();
        if (ImGui::Button("Ок"))
        {
            show_window = false;
            show_dialog_topinfo = false;
        }
        ImGui::End();
    }
    // L2DFileDialog code goes here.

    // End L2DFileDialog code.

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(objGLFW->getGlfwWindow());
}

InterfaceCAD::InterfaceCAD(GlfwOcctView *obj):objView(obj)
{
    objModelingCascade = std::make_unique<ModelingCascade>();
}

InterfaceCAD::~InterfaceCAD()
{

}

void InterfaceCAD::clearImGUI()
{
    // Cleanup IMGUI.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
