ledX=2.77;
ledY=3.4;
ledZ=1.81;
offset = 8; //ledX*2;
sz=20;

$fn=16;
module LED()
{
    union() {
      color("Black",0.1) cube([ledX,ledY,ledZ], center=true);
        
      translate([ledX/3,ledY/3,0.5]) color("red")
        cube(ledY/3,center=true);
        
      translate([-ledX/3,ledY/3,0.5]) color("GreenYellow")
        cube(ledY/3,center=true);
        
      translate([-ledX/3,-ledY/3,0.5]) color("Blue")
        cube(ledY/3,center=true);
        
      translate([ledX/3,-ledY/3,0.5]) color("Black")
        cube(ledY/3,center=true);
    }
}

translate([-1.5*offset,-1.5*offset,-1.5*offset])
{
  for(x = [0 : 3])
    for(y = [0 : 3])
      for(z = [0 : 3])
        translate([x*offset,y*offset,z*offset])
        {
            rotate([0,0,-z*90])
              LED();
        };
  }

//color(yellow,0.2)
//  cube([sz,sz,sz], center=true);
