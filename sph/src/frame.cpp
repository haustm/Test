#include <vtkVersion.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

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
			tmp.x = i * 0.1 ;
			tmp.y = j * 0.1 ;
			tmp.z = 0;
			newF.particles.push_back(tmp);
		}
    }

    return newF;    
}


void Frame::writeFrame()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (auto i : particles)
    {
        points->InsertNextPoint ( i.x, i.y, i.z );
    }


    // Create a polydata object and add the points to it.
    vtkSmartPointer<vtkPolyData> polydata =  vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    // Write the file
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("test.vtp");
    writer->SetInputData(polydata);

    writer->Write();

}
