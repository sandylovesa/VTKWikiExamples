#ifndef __vtkTest_h
#define __vtkTest_h

#include "vtkDataObject.h"

class vtkTest : public vtkDataObject
{
  public:
    static vtkTest* New();
    vtkTypeRevisionMacro(vtkTest,vtkDataObject);
    void PrintSelf( ostream& os, vtkIndent indent );

    vtkGetMacro(Value, double);
    
  protected:
    vtkTest();
    ~vtkTest();

  private:
    vtkTest( const vtkTest& ); // Not implemented.
    void operator = ( const vtkTest& ); // Not implemented.
    
    double Value;
};

#endif 
