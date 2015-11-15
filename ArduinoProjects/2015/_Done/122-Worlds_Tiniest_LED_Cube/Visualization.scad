offset = 5;
ledX=3.4;
ledY=2.77;
ledZ=1.81;
sz=20;

translate([-1.5*offset,-1.5*offset,-1.5*offset])
{
  for(x = [0 : 3])
    for(y = [0 : 3])
      for(z = [0 : 3])
        translate([x*offset,y*offset,z*offset])
          cube([ledX,ledY,ledZ], center=true);
  }

color(green,0.2)
  cube([sz,sz,sz], center=true);
