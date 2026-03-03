#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkOpenVRCamera.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkOpenVRRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>

int main(int argc, char* argv[])
{
    (void)argc; (void)argv;

    vtkNew<vtkCylinderSource> cyl;
    cyl->SetRadius(0.2);
    cyl->SetHeight(1.0);
    cyl->SetResolution(64);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cyl->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkOpenVRRenderer> renderer;
    renderer->AddActor(actor);

    vtkNew<vtkOpenVRRenderWindow> rw;
    rw->AddRenderer(renderer);
    rw->SetWindowName("Worksheet7 Exercise2 - OpenVR Cylinder");

    vtkNew<vtkOpenVRRenderWindowInteractor> iren;
    iren->SetRenderWindow(rw);

    rw->Render();
    iren->Initialize();
    iren->Start();

    return 0;
}