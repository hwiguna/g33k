ledX=3.4;
ledY=2.77;
ledZ=1.81;
offset = 5; //ledX*2;
sz=20;

$fn=16;
module LED()
{
    //difference() {
      cube([ledX,ledY,ledZ], center=true);
      translate([0,0,0.7])
        circle(d=ledY-0.3);
    //};
}

translate([-1.5*offset,-1.5*offset,-1.5*offset])
{
  for(x = [0 : 3])
    for(y = [0 : 3])
      for(z = [0 : 3])
        translate([x*offset,y*offset,z*offset])
        {
          if (z==1 || z==3) {
            rotate([0,0, 90])
              LED();}
          else {
            rotate([0,0, 0])
              LED();
          };
        };
  }

color(green,0.2)
  cube([sz,sz,sz], center=true);
