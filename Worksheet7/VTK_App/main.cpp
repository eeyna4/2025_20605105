#include <iostream>

#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "[VTK] Program start" << std::endl;

    vtkNew<vtkSphereSource> sphere;
    sphere->SetRadius(0.5);
    sphere->SetThetaResolution(32);
    sphere->SetPhiResolution(32);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphere->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.3);

    vtkNew<vtkRenderWindow> rw;
    rw->AddRenderer(renderer);
    rw->SetSize(900, 600);
    rw->SetWindowName("Worksheet7 VTK Sphere");

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(rw);

    std::cout << "[VTK] Before Render()" << std::endl;
    rw->Render();

    std::cout << "[VTK] Before Initialize()" << std::endl;
    iren->Initialize();

    std::cout << "[VTK] Before Start() (window should appear now)" << std::endl;
    iren->Start();

    std::cout << "[VTK] After Start() (printed after window closes)" << std::endl;
    return 0;
}