/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2006 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 0.9.6, packaged on June, 2006.

 http://glc-lib.sourceforge.net

 GLC-lib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 GLC-lib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with GLC-lib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*****************************************************************************/

//! \file glc_factory.cpp implementation of the GLC_Factory class.

#include "glc_factory.h"
#include "glc_objtomesh2.h"

// init static member
GLC_Factory* GLC_Factory::m_pFactory= NULL;

//////////////////////////////////////////////////////////////////////
// static method
//////////////////////////////////////////////////////////////////////
// Return the unique instance of the factory
GLC_Factory* GLC_Factory::instance(QGLWidget *GLWidget)
{
	if(m_pFactory == NULL)
	{
		m_pFactory= new GLC_Factory(GLWidget);
	}
	return m_pFactory;
}

//////////////////////////////////////////////////////////////////////
// Constructor destructor
//////////////////////////////////////////////////////////////////////

// Protected constructor
GLC_Factory::GLC_Factory(QGLWidget *GLWidget)
: m_pQGLWidget(GLWidget)
{
	
}

// Destructor
GLC_Factory::~GLC_Factory()
{
	m_pFactory= NULL;
}

//////////////////////////////////////////////////////////////////////
// Create functions
//////////////////////////////////////////////////////////////////////

// Create an GLC_Point
GLC_Point* GLC_Factory::createPoint(const GLC_Vector4d &coord) const
{
	return new GLC_Point(coord);
}
// Create an GLC_Point
GLC_Point* GLC_Factory::createPoint(double x, double y, double z) const
{
	return new GLC_Point(x, y, z);
}

//  Create an GLC_Circle
GLC_Circle* GLC_Factory::createCircle(double radius, double angle) const
{
	return new GLC_Circle(radius, angle);
}
// Create an GLC_Circle by copying another GLC_Circle
GLC_Circle* GLC_Factory::createCircle(const GLC_Geometry* pCircle) const
{
	const GLC_Circle* pTempCircle= dynamic_cast<const GLC_Circle*>(pCircle);
	if (pTempCircle != NULL)
	{
		return new GLC_Circle(*pTempCircle);
	}
	else
	{
		return NULL;
	}	
}
// Create an GLC_Box
GLC_Box* GLC_Factory::createBox(double lx, double ly, double lz) const
{
	return new GLC_Box(lx, ly, lz);
}

// Create an GLC_Box
GLC_Box* GLC_Factory::createBox(const GLC_BoundingBox& boundingBox) const
{
	const double lx= boundingBox.getUpper().getX() - boundingBox.getLower().getX();
	const double ly= boundingBox.getUpper().getY() - boundingBox.getLower().getY();
	const double lz= boundingBox.getUpper().getZ() - boundingBox.getLower().getZ();
	GLC_Box* pBox= new GLC_Box(lx, ly, lz);
	pBox->translate(boundingBox.getLower().getX(), boundingBox.getLower().getY()
					, boundingBox.getLower().getZ());
					
	return pBox;
}

// Create an GLC_Cylinder
GLC_Cylinder* GLC_Factory::createCylinder(double radius, double length) const
{
	return new GLC_Cylinder(radius, length);
}
// Create an GLC_Cylinder by copying another GLC_Cylinder
GLC_Cylinder* GLC_Factory::createCylinder(const GLC_Geometry* pCylinder) const
{
	const GLC_Cylinder* pTempCylinder= dynamic_cast<const GLC_Cylinder*>(pCylinder);
	if (pTempCylinder != NULL)
	{
		return new GLC_Cylinder(*pTempCylinder);
	}
	else
	{
		return NULL;
	}
}
// Create an GLC_Mesh with the name of the obj file
GLC_Mesh2* GLC_Factory::createMesh(const std::string &fullfileName) const
{
	GLC_ObjToMesh2 objToMesh(m_pQGLWidget);
	return objToMesh.CreateMeshFromObj(fullfileName);
}

// Create an GLC_Mesh with a QFile
GLC_Mesh2* GLC_Factory::createMesh(const QFile &file) const
{
	GLC_ObjToMesh2 objToMesh(m_pQGLWidget);
	return objToMesh.CreateMeshFromObj(file.fileName().toStdString());
}

// Create an GLC_Mesh by copying another mesh
GLC_Mesh2* GLC_Factory::createMesh(const GLC_Geometry* pMesh) const
{	
	const GLC_Mesh2* pTempMesh= dynamic_cast<const GLC_Mesh2*>(pMesh);
	if (pTempMesh != NULL)
	{
		return new GLC_Mesh2(*pTempMesh);
	}
	else
	{
		return NULL;
	}
}

// Create an GLC_Material
GLC_Material* GLC_Factory::createMaterial() const
{
	return new GLC_Material();
}

// Create an GLC_Material
GLC_Material* GLC_Factory::createMaterial(const GLfloat *pAmbiantColor) const
{
	return new GLC_Material("Material", pAmbiantColor);
}
// Create an GLC_Material
GLC_Material* GLC_Factory::createMaterial(const QColor &color) const
{
	return new GLC_Material(color);
}

GLC_Material* GLC_Factory::createMaterial(GLC_Texture* pTexture) const
{
	return new GLC_Material(pTexture, "TextureMaterial");
}
// create an material textured with a image file name
GLC_Material* GLC_Factory::createMaterial(const QString &textureFullFileName) const
{
	GLC_Texture* pTexture= createTexture(textureFullFileName);
	return createMaterial(pTexture);	
}

// Create an GLC_Texture

GLC_Texture* GLC_Factory::createTexture(const QString &textureFullFileName) const
{
	return new GLC_Texture(m_pQGLWidget, textureFullFileName);
}
