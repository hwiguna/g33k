offset = 5;
ledWidth=3.49;
ledHeight=1.77;
ledDepth=2.77;
sz=24;


module Jig()
{
  difference()
  {
      Surface();
      
      for(x = [0 : 3])
        for(y = [0 : 3]) 
            translate([x*offset,y*offset,0])
        if (y==1 || y==3) {
              LED(); // Comment this to print shallow jig
            }
          else {
              LEDUpright();
          };
              
  }
}

module LED()
{
    cube([ledWidth,ledHeight,1], center=true);
}


module LEDUpright()
{
    cube([ledDepth,ledHeight,1], center=true);
}

module Surface()
{
  translate([1.5*offset,1.5*offset,0])
  cube([sz,sz,1],center=true); 
}


projection()
{
  //Surface();
  Jig();
}