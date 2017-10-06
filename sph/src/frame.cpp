#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <iostream>

#include "frame.hpp"
#include "particle.hpp"

Frame Frame::initNew()
{
    Frame newF = Frame();
    
    for(int i = 0; i < 100; i++)
    {
		for(int j = 0; j < 100; j++)
		{
			Particle tmp;
			tmp.pos[0] = i * 0.1 ;
			tmp.pos[1] = j * 0.1 ;
			tmp.pos[2] = 0;
			newF.particles.push_back(tmp);
		}
    }

    return newF;    
}


void Frame::writeFrame()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        points->InsertNextPoint ( it->pos[0], it->pos[1], it->pos[2] );
    }


    // Create a polydata object and add the points to it.
    vtkSmartPointer<vtkPolyData> polydata =  vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

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
        it->calcForces();
    }

    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        it->move(0.1);
    }

    this->time += 0.1;

}
