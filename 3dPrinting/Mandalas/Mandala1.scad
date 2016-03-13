$fn=32;
border=1;
outR = 10;
outT = 0.5;

R1 = 5;
th = 0.2;

module cir(r,t)
{
difference()
{
	cylinder(th,r,r);
	cylinder(th,r-t, r-t);
}
}

for (q=[0:90:360])
rotate([0,0,q])
cube([outR+border,outR+border,0.1]);

cir(outR,outT);
cir(R1,outT);

/*
for (i=[1:6])
	for (rot=[0:60/(i):360])
		rotate([0,0,rot])
		{
			union() {
				translate([i*5+2.5,0,0])
					cylinder(1,1.5,1.5);
				translate([i*5,-0.5,0])
					cube([8,1,1]);
			}
		}
*/