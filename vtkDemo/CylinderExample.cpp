//
// Created by Yukiix on 20/03/2024.
//
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <X11/Xlib.h>

#include <array>

int main(int, char*[])
{
//    Display* display;
//    Window window;
//    Screen* screen;
//    int screenId;
//    XEvent ev;
//
//    display = XOpenDisplay(NULL);
//    if (display == nullptr)
//    {
//        std::cerr << "Could not open display" << std::endl;
//        return EXIT_FAILURE;
//    }
//    screen = DefaultScreenOfDisplay(display);
//    screenId = DefaultScreen(display);

    // Open the window
//    window = XCreateSimpleWindow(display, RootWindowOfScreen(screen), 0, 0, 320, 200, 1, BlackPixel(display, screenId), WhitePixel(display, screenId));
//
//    // Show the window
//    XClearWindow(display, window);
//    XMapRaised(display, window);

    vtkNew<vtkNamedColors> colors;

    // Set the background color.
    std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e, in practice an octagonal prism).
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are
    // defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    // The renderer generates the image
    // which is then displayed on the render window.
    // It can be thought of as a scene to which the actor is added
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);
    renderer->SetViewport(0, 0, 1, 1);

    // The render window is the actual GUI window
    // that appears on the computer screen
    vtkNew<vtkRenderWindow> renderWindow;
    int winsize = 300;
    renderWindow->SetSize(winsize, winsize);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("Cylinder");
//    renderWindow->SetOffScreenRendering(1);

    // The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // This starts the event loop and as a side effect causes an initial render.
    renderWindow->Render();
    renderWindowInteractor->Start();

//    vtkNew<vtkRenderWindow> renderWindow;
//    renderWindow->SetOffScreenRendering(1);
//    renderWindow->AddRenderer(renderer);
//    unsigned char* rgba = renderWindow->GetRGBACharPixelData(0, 0, winsize - 1, winsize - 1, 0);
//    XImage* image = XCreateImage(display, CopyFromParent, 24, ZPixmap, 0, reinterpret_cast<char *>(rgba), winsize, winsize, 32, 0);
//    XPutImage(display, window, DefaultGC(display, screenId), image, 0, 0, 0, 0, winsize, winsize);
//    XFlush(display);

//    printf("support opengl %s\n", renderWindow->SupportsOpenGL() ? "true" : "false");
//    XSelectInput (display, window, ExposureMask | KeyPressMask | ButtonPressMask);
//
//    while (true)
//    {
//        XNextEvent(display, &ev);
//        switch(ev.type){
//            case Expose:
//                break;
//            case KeyPress:
//                char buf[100];
//                sprintf(buf,"x=%3d,y=%3d", ev.xbutton.x, ev.xbutton.y);
//                XDrawString (display, window, DefaultGC(display, screenId), ev.xbutton.x, ev.xbutton.y,
//                             buf, strlen(buf));
//        }
//    }
//    XDestroyWindow(display, window);
//    XFree(screen);
//    XCloseDisplay(display);
    return EXIT_SUCCESS;
}