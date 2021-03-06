// Created on: 2004-05-11
// Created by: Sergey ZARITCHNY <szy@opencascade.com>
// Copyright (c) 2004-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _BinTools_ShapeSet_HeaderFile
#define _BinTools_ShapeSet_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <TopTools_IndexedMapOfShape.hxx>
#include <BinTools_FormatVersion.hxx>
#include <BinTools_LocationSet.hxx>
#include <Standard_Integer.hxx>
#include <BRep_Builder.hxx>
#include <BinTools_SurfaceSet.hxx>
#include <BinTools_CurveSet.hxx>
#include <BinTools_Curve2dSet.hxx>
#include <TColStd_IndexedMapOfTransient.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <TopAbs_ShapeEnum.hxx>

class TopoDS_Shape;
class BinTools_LocationSet;


//! Writes topology in OStream in binary format
class BinTools_ShapeSet 
{
public:

  DEFINE_STANDARD_ALLOC

  //! Builds an empty ShapeSet.
  //! @param theWithTriangles [in] flag to write triangulation data
  Standard_EXPORT BinTools_ShapeSet (const Standard_Boolean theWithTriangles = Standard_False);

  Standard_EXPORT virtual ~BinTools_ShapeSet();

  //! Return true if shape should be stored with triangles.
  Standard_Boolean IsWithTriangles() const { return myWithTriangles; }

  //! Define if shape will be stored with triangles.
  //! Ignored (always written) if face defines only triangulation (no surface).
  void SetWithTriangles (const Standard_Boolean theWithTriangles) { myWithTriangles = theWithTriangles; }

  //! Sets the BinTools_FormatVersion.
  Standard_EXPORT void SetFormatNb (const Standard_Integer theFormatNb);

  //! Returns the BinTools_FormatVersion.
  Standard_EXPORT Standard_Integer FormatNb() const;
  
  //! Clears the content of the set.
  Standard_EXPORT virtual void Clear();
  
  //! Stores <S> and its sub-shape. Returns the index of <S>.
  //! The method AddGeometry is called on each sub-shape.
  Standard_EXPORT Standard_Integer Add (const TopoDS_Shape& S);
  
  //! Returns the sub-shape of index <I>.
  Standard_EXPORT const TopoDS_Shape& Shape (const Standard_Integer I) const;
  
  //! Returns the index of <S>.
  Standard_EXPORT Standard_Integer Index (const TopoDS_Shape& S) const;
  
  Standard_EXPORT const BinTools_LocationSet& Locations() const;
  
  Standard_EXPORT BinTools_LocationSet& ChangeLocations();
  
  //! Returns number of shapes read from file.
  Standard_EXPORT Standard_Integer NbShapes() const;
  
  //! Writes the content of  me  on the stream <OS> in binary
  //! format that can be read back by Read.
  //!
  //! Writes the locations.
  //!
  //! Writes the geometry calling WriteGeometry.
  //!
  //! Dumps the shapes from last to first.
  //! For each shape  :
  //! Write the type.
  //! calls WriteGeometry(S).
  //! Write the flags, the subshapes.
  Standard_EXPORT virtual void Write
    (Standard_OStream& OS,
     const Message_ProgressRange& theRange = Message_ProgressRange()) const;
  
  //! Reads the content of me from the binary stream  <IS>. me
  //! is first cleared.
  //!
  //! Reads the locations.
  //!
  //! Reads the geometry calling ReadGeometry.
  //!
  //! Reads the shapes.
  //! For each shape
  //! Reads the type.
  //! calls ReadGeometry(T,S).
  //! Reads the flag, the subshapes.
  Standard_EXPORT virtual void Read
    (Standard_IStream& IS,
        const Message_ProgressRange& theRange = Message_ProgressRange());
  
  //! Writes   on  <OS>   the shape   <S>.    Writes the
  //! orientation, the index of the TShape and the index
  //! of the Location.
  Standard_EXPORT virtual void Write (const TopoDS_Shape& S, Standard_OStream& OS) const;
  
  //! Writes the geometry of  me  on the stream <OS> in a
  //! binary format that can be read back by Read.
  Standard_EXPORT virtual void WriteGeometry
    (Standard_OStream& OS,
        const Message_ProgressRange& theRange = Message_ProgressRange()) const;
  
  //! Reads the geometry of me from the  stream  <IS>.
  Standard_EXPORT virtual void ReadGeometry
    (Standard_IStream& IS,
        const Message_ProgressRange& theRange = Message_ProgressRange());
  
  //! Reads  from <IS>  a shape  and  returns  it in  S.
  //! <NbShapes> is the number of tshapes in the set.
  Standard_EXPORT virtual void Read
    (TopoDS_Shape& S,
     Standard_IStream& IS, const Standard_Integer NbShapes) const;
  
  //! Writes the geometry of <S>  on the stream <OS> in a
  //! binary format that can be read back by Read.
  Standard_EXPORT virtual void WriteGeometry (const TopoDS_Shape& S, Standard_OStream& OS) const;
  
  //! Reads the geometry of a shape of type <T> from the
  //! stream <IS> and returns it in <S>.
  Standard_EXPORT virtual void ReadGeometry (const TopAbs_ShapeEnum T, Standard_IStream& IS, TopoDS_Shape& S);
  
  //! Stores the goemetry of <S>.
  Standard_EXPORT virtual void AddGeometry (const TopoDS_Shape& S);
  
  //! Inserts  the shape <S2> in  the  shape <S1>.
  Standard_EXPORT virtual void AddShapes (TopoDS_Shape& S1, const TopoDS_Shape& S2);
  
  //! Reads the 3d polygons  of me
  //! from the  stream  <IS>.
  Standard_EXPORT void ReadPolygon3D
    (Standard_IStream& IS,
        const Message_ProgressRange& theRange = Message_ProgressRange());
  
  //! Writes the 3d polygons
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WritePolygon3D
    (Standard_OStream& OS,
        const Message_ProgressRange& theRange = Message_ProgressRange()) const;
  
  //! Reads the triangulation of me
  //! from the  stream  <IS>.
  Standard_EXPORT void ReadTriangulation
    (Standard_IStream& IS,
        const Message_ProgressRange& theRange = Message_ProgressRange());
  
  //! Writes the triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WriteTriangulation
    (Standard_OStream& OS,
        const Message_ProgressRange& theRange = Message_ProgressRange()) const;
  
  //! Reads the polygons on triangulation of me
  //! from the  stream  <IS>.
  Standard_EXPORT void ReadPolygonOnTriangulation
    (Standard_IStream& IS,
        const Message_ProgressRange& theRange = Message_ProgressRange());
  
  //! Writes the polygons on triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WritePolygonOnTriangulation
    (Standard_OStream& OS,
        const Message_ProgressRange& theRange = Message_ProgressRange()) const;

public:

  static Standard_CString Version_1;
  static Standard_CString Version_2;
  static Standard_CString Version_3;

private:

  TopTools_IndexedMapOfShape myShapes;
  BinTools_LocationSet myLocations;
  Standard_Integer myFormatNb;
  BRep_Builder myBuilder;
  BinTools_SurfaceSet mySurfaces;
  BinTools_CurveSet myCurves;
  BinTools_Curve2dSet myCurves2d;
  NCollection_IndexedMap<Handle(Poly_Polygon2D), TColStd_MapTransientHasher> myPolygons2D;
  NCollection_IndexedMap<Handle(Poly_Polygon3D), TColStd_MapTransientHasher> myPolygons3D;
  NCollection_IndexedMap<Handle(Poly_Triangulation), TColStd_MapTransientHasher> myTriangulations;
  NCollection_IndexedMap<Handle(Poly_PolygonOnTriangulation), TColStd_MapTransientHasher> myNodes;
  Standard_Boolean myWithTriangles;

};

#endif // _BinTools_ShapeSet_HeaderFile
