#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <iostream>
#include <cmath>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkFloatArray.h>

#include "frame.hpp"
#include "particle.hpp"

Frame Frame::initNew()
{
    Frame newF = Frame();
    newF.dt = 0.0001;
    
    int id = 0;
    for(int i = 0; i < 20; i++)
    {
		for(int j = 0; j < 20; j++)
		{
			Particle tmp(&newF);
			tmp.pos[0] = i * 0.05  ;
			tmp.pos[1] = j * 0.05 + 0.0;
			tmp.pos[2] = 0;
            tmp.id = id; id++;
            //if (sqrt((tmp.pos[0]*tmp.pos[0]) +(tmp.pos[1]*tmp.pos[1]) + (tmp.pos[2]*tmp.pos[2]) ) < 0.8)
            {
              newF.particles.push_back(tmp);
            }

		}
    }
    newF.N = id;

    return newF;    
}


void Frame::writeFrame()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkFloatArray> densities = vtkSmartPointer<vtkFloatArray>::New();
    densities->SetNumberOfComponents(1);
    densities->SetName("rho");

    vtkSmartPointer<vtkFloatArray> pressures = vtkSmartPointer<vtkFloatArray>::New();
    pressures->SetNumberOfComponents(1);
    pressures->SetName("p");
 
    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        points->InsertNextPoint ( it->pos[0], it->pos[1], it->pos[2]);
        densities->InsertNextValue(it->rho);
        pressures->InsertNextValue(it->press);
    }

    // Create a polydata object and add the points to it.
    vtkSmartPointer<vtkPolyData> polydata =  vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->GetPointData()->AddArray(densities);
    polydata->GetPointData()->AddArray(pressures);


    // Write the file
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    std::string filename = "t." + std::to_string(int(this->time/this->dt)) +".vtp";
    writer->SetFileName(filename.c_str());
    writer->SetInputData(polydata);

    writer->Write();

}

void Frame::step()
{

    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        it->move(dt);
    }

    this->time += dt;

}


double Frame::kern(double x, double h)
{
    if (x > 3*h) return 0;
    return exp(-1.0*x*x/(h*h)) / (h*h*(3.14159));
}


Vector3d Frame::gradKern(Vector3d a, Vector3d b,  double h)
{
    Vector3d zero;
    zero << 0,0,0;
    double x = (a - b).norm();
    if( x > 3*h) return zero;
    double deriv = (-2.0*x*exp(-1.0*x*x/(h*h)) / (h*h*h*h*sqrt(3.14159))) ;
    Vector3d tmp = deriv * ( a -b ) / x;
    return tmp; 
    
}

double Frame::kern2(double x, double h)
{
    double w = 10.0/(7.0 * 3.141592 * h * h);
    if( x >= 0 and x <= 1.0) w = w * (1 - 3.0/2.0* x*x * (1 - 0.5*x));
    else if (x > 1.0 and x <= 2.0) w = w / 4 * pow((2 - x), 3);
    else w = 0.0;
    return w;    
}


Vector3d Frame::gradKern2(Vector3d a, Vector3d b,  double h)
{
    Vector3d zero;
    zero << 0,0,0;
    double x = (a - b).norm()/h;
    double w = 10.0/(7.0 * 3.141592 * h * h);
    if( x >= 0 and x <= 1.0) w = w * (0.75*x*x - 3*(1-0.5*x)*x);
    else if (x > 1.0 and x <= 2.0) w = -3.0/4.0 * w * pow((2 - x), 2) ;
    else return zero;
    
    Vector3d tmp = w * ( a - b ) / (a-b).norm();
    return tmp; 
    
}

double Frame::kern3(double x, double h)
{
    return 0;
}


Vector3d Frame::gradKern3(Vector3d a, Vector3d b, double h)
{
    Vector3d x;
    return x;
}



void Frame::findNeighbours()
{
    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        for(std::vector<Particle>::iterator jt = particles.begin(); jt != particles.end(); ++jt)
        {
            if( abs((it->pos - jt->pos).norm()) < 4*it->h ) it->neighbours.push_back(&(*jt));
        }
    }
}
