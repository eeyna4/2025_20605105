#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  auto sphere = vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(0.5);
  sphere->SetThetaResolution(32);
  sphere->SetPhiResolution(32);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphere->GetOutputPort() );

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.3);

  auto rw = vtkSmartPointer<vtkRenderWindow>::New();
  rw->AddRenderer(renderer);
  rw->SetSize(900, 600);

  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(rw);

  rw->Render();
  iren->Start();
  return 0;
}
