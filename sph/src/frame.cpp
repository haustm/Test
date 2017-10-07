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
    
    int id = 0;
    for(int i = 0; i < 10; i++)
    {
		for(int j = 0; j < 10; j++)
		{
			Particle tmp;
			tmp.pos[0] = i * 0.1 ;
			tmp.pos[1] = j * 0.1 ;
			tmp.pos[2] = 0;
            tmp.id = id; id++;
			newF.particles.push_back(tmp);
		}
    }

    return newF;    
}


void Frame::writeFrame()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkFloatArray> densities = vtkSmartPointer<vtkFloatArray>::New();
    densities->SetNumberOfComponents(1);
    densities->SetName("rho");
 
    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        points->InsertNextPoint ( it->pos[0], it->pos[1], it->pos[2]);
        densities->InsertNextValue(it->rho);
    }

    // Create a polydata object and add the points to it.
    vtkSmartPointer<vtkPolyData> polydata =  vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->GetPointData()->AddArray(densities);


    // Write the file
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    std::string filename = "t." + std::to_string(int(this->time/0.1)) +".vtp";
    writer->SetFileName(filename.c_str());
    writer->SetInputData(polydata);

    writer->Write();

}

void Frame::step()
{

    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        it->move(0.1);
    }

    this->time += 0.1;

}


double Frame::kern(double x, double h)
{
    return exp(-1.0*x*x/(h*h)) / (h*sqrt(3.14159));
}

double Frame::gradKern(double x, double h)
{
    return -2.0*x*exp(-1.0*x*x/(h*h)) / (h*h*h*sqrt(3.14159));
}

void Frame::findNeighbours()
{
    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        for(std::vector<Particle>::iterator jt = particles.begin(); jt != particles.end(); ++jt)
        {
            it->neighbours.push_back(&(*jt));
        }
    }
}
