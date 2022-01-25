#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    camera = Camera(Point3f(0.f, 0.f, 10.f), Point3f(0.f, 0.f, 0.f),
                    Vector3f(0.f, 1.f, 0.f), 45.f, 0.1, 1000.f, 400, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
create a QImage, write color to each pixel in the image,
and save the QImage as a .png file with a QFileDialog prompt
for determining the file name and save location.
*/
void MainWindow::on_pushButton_clicked()
{
    // pick a location to save image
    QString directory = QFileDialog::getExistingDirectory(this, QString("Open"));

    // test raycasting code
    QImage image(camera.m_pixelW, camera.m_pixelH, QImage::Format_RGB32);
    image.fill(Qt::GlobalColor::black);

    for(int i = 0; i < camera.m_pixelH; i++)
    {
        for(int j = 0; j < camera.m_pixelW; j++)
        {
            Ray curr = camera.rayCast(i, j);
            Color3f c = (curr.m_dir + Vector3f(1.f, 1.f, 1.f)) * 0.5f * 255.f;
            image.setPixel(i, j, qRgb(c.x, c.y, c.z));
        }
    }
    image.save(directory + "/TestRayCasting.png", "PNG");
    // display image in a label
    QPixmap pic(directory + "/TestRayCasting.png");
    ui->label->setPixmap(pic);
}

// sphere intersection, no transform
void MainWindow::on_pushButton_2_clicked()
{
    // pick a location to save image
    QString directory = QFileDialog::getExistingDirectory(this, QString("Open"));
    QImage image(camera.m_pixelW, camera.m_pixelH, QImage::Format_RGB32);
    image.fill(Qt::GlobalColor::black);

    Transform transform = Transform();
//    Transform sphereTrans = Transform(Vector3f(-1.f, 1.f, 0.f),
//                                      Vector3f(0.f),
//                                      Vector3f(2.f, 4.f, 2.f));
    sphere = Sphere();
    sphere.m_transform = transform;

    for(int i = 0; i < camera.m_pixelH; i++)
    {
        for(int j = 0; j < camera.m_pixelW; j++)
        {
            Ray curr = camera.rayCast(i, j);
            if(sphere.getIntersection(curr) != std::nullopt)
            {
                Intersection intersection = sphere.getIntersection(curr).value();
                Color3f c = (intersection.m_normal + Vector3f(1.f, 1.f, 1.f)) * 0.5f * 255.f;
                image.setPixel(i, j, qRgb(c.x, c.y, c.z));
            }
        }
    }
    image.save(directory + "/TestIntersection1.png", "PNG");
    // display image in a label
    QPixmap pic(directory + "/TestIntersection1.png");
    ui->label->setPixmap(pic);
}

// test plane intersection, no transform
void MainWindow::on_pushButton_3_clicked()
{
    // pick a location to save image
    QString directory = QFileDialog::getExistingDirectory(this, QString("Open"));
    QImage image(camera.m_pixelW, camera.m_pixelH, QImage::Format_RGB32);
    image.fill(Qt::GlobalColor::black);

    Transform transform = Transform();
//    Transform squareTrans = Transform(Vector3f(0.f, 0.f, -5.f),
//                                      Vector3f(0.f, 30.f, 0.f),
//                                      Vector3f(10.f, 10.f, 1.f));
    squarePlane = SquarePlane();
    squarePlane.m_transform = transform;

    for(int i = 0; i < camera.m_pixelH; i++)
    {
        for(int j = 0; j < camera.m_pixelW; j++)
        {
            Ray curr = camera.rayCast(i, j);
            if(squarePlane.getIntersection(curr) != std::nullopt)
            {
                Intersection intersection = squarePlane.getIntersection(curr).value();
                Color3f c = (intersection.m_normal + Vector3f(1.f, 1.f, 1.f)) * 0.5f * 255.f;
                image.setPixel(i, j, qRgb(c.x, c.y, c.z));
            }
        }
    }
    image.save(directory + "/TestIntersection2.png", "PNG");
    // display image in a label
    QPixmap pic(directory + "/TestIntersection2.png");
    ui->label->setPixmap(pic);
}

// Sphere: T(-1, 1, 0), S(2, 4, 2)
// SquarePlane: T(0, 0, -5), R(0, 30, 0), S(10, 10, 1).
void MainWindow::on_pushButton_4_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, QString("Open"));
    QImage image(camera.m_pixelW, camera.m_pixelH, QImage::Format_RGB32);
    image.fill(Qt::GlobalColor::black);

    Transform sphereTrans = Transform(Vector3f(-1.f, 1.f, 0.f),
                                      Vector3f(0.f),
                                      Vector3f(2.f, 4.f, 2.f));
    Transform squareTrans = Transform(Vector3f(0.f, 0.f, -5.f),
                                      Vector3f(0.f, 30.f, 0.f),
                                      Vector3f(10.f, 10.f, 1.f));
    sphere = Sphere();
    sphere.m_transform = sphereTrans;
    squarePlane = SquarePlane();
    squarePlane.m_transform = squareTrans;
    scene = Scene(camera);

    uPtr<Primitive> primitive1 = mkU<Primitive>(Primitive());
    primitive1->m_shape = mkU<Sphere>(sphere);
    uPtr<Primitive> primitive2 = mkU<Primitive>(Primitive());
    primitive2->m_shape = mkU<SquarePlane>(squarePlane);

    scene.m_primitiveVector.push_back(std::move(primitive1));
    scene.m_primitiveVector.push_back(std::move(primitive2));

    for(int i = 0; i < camera.m_pixelH; i++)
    {
        for(int j = 0; j < camera.m_pixelW; j++)
        {
            Ray curr = camera.rayCast(i, j);
            Intersection* intersection = new Intersection();
            if(scene.getIntersection(curr, intersection))
            {
                Color3f c = (intersection->m_normal + Vector3f(1.f, 1.f, 1.f)) * 0.5f * 255.f;
                image.setPixel(i, j, qRgb(c.x, c.y, c.z));
            }
        }
    }
    image.save(directory + "/TestIntersection3.png", "PNG");
    // display image in a label
    QPixmap pic(directory + "/TestIntersection3.png");
    ui->label->setPixmap(pic);
}

// Sphere: T(0, 0, 1), R(0, 0, 45), S(2, 1, 1)
// Sphere: T(0, 0, 1), R(0, 0, 45), S(2, 1, 1)
// SquarePlane: T(0, -0.5, 0), R(90, 0, 0), S(5, 5, 1).
void MainWindow::on_pushButton_5_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, QString("Open"));
    QImage image(camera.m_pixelW, camera.m_pixelH, QImage::Format_RGB32);
    image.fill(Qt::GlobalColor::black);

    Transform sphereTrans = Transform(Vector3f(0.f, 0.f, 1.f),
                                      Vector3f(0.f, 0.f, 45.f),
                                      Vector3f(2.f, 1.f, 1.f));
    Transform sphereTrans1 = Transform(Vector3f(0.f, 0.f, 1.f),
                                      Vector3f(0.f, 0.f, 45.f),
                                      Vector3f(2.f, 1.f, 1.f));
    Transform squareTrans = Transform(Vector3f(0.f, -0.5f, 0.f),
                                      Vector3f(90.f, 0.f, 0.f),
                                      Vector3f(5.f, 5.f, 1.f));
    sphere = Sphere();
    sphere.m_transform = sphereTrans;
    sphere1 = Sphere();
    sphere1.m_transform = sphereTrans1;
    squarePlane = SquarePlane();
    squarePlane.m_transform = squareTrans;
    scene = Scene(camera);

    uPtr<Primitive> primitive1 = mkU<Primitive>(Primitive());
    primitive1->m_shape = mkU<Sphere>(sphere);
    uPtr<Primitive> primitive2 = mkU<Primitive>(Primitive());
    primitive2->m_shape = mkU<Sphere>(sphere1);
    uPtr<Primitive> primitive3 = mkU<Primitive>(Primitive());
    primitive3->m_shape = mkU<SquarePlane>(squarePlane);

    scene.m_primitiveVector.push_back(std::move(primitive1));
    scene.m_primitiveVector.push_back(std::move(primitive2));
    scene.m_primitiveVector.push_back(std::move(primitive3));

    for(int i = 0; i < camera.m_pixelH; i++)
    {
        for(int j = 0; j < camera.m_pixelW; j++)
        {
            Ray curr = camera.rayCast(i, j);
            Intersection* intersection = new Intersection();
            if(scene.getIntersection(curr, intersection))
            {
                Color3f c = (intersection->m_normal + Vector3f(1.f, 1.f, 1.f)) * 0.5f * 255.f;
                image.setPixel(i, j, qRgb(c.x, c.y, c.z));
            }
        }
    }
    image.save(directory + "/TestIntersection4.png", "PNG");
    // display image in a label
    QPixmap pic(directory + "/TestIntersection4.png");
    ui->label->setPixmap(pic);
}













