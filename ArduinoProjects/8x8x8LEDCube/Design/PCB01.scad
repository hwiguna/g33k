pcbX=200;
pcbY=150;
pcbZ=0.2;

p=2.54; // Pitch (distance between holes)
s=7; // How many holes apart should the LEDs be mounted on the PCB
L=s*p; // LED lead length

translate([-pcbX/2,-pcbY/2, -8*s*p/2]) {
	pcb();
	//led();
	//theLayer();
	theCube();
	//translate([p*s*(8+1),p*s*2,0]) chip(20);
	theChips();
}

module pcb()
{
	difference() {
		color([0,0,0])
			cube([pcbX,pcbY,pcbZ]);
	
		// Holes
		for (x=[0:p:pcbX]) {
			translate([x,p,0])
				cube([1,1,pcbZ*2],center=true);
		}

		for (y=[0:p:pcbY]) {
			translate([p,y,0])
				cube([1,1,pcbZ*2],center=true);
		}
	}
};

module led() {
	// LED
	color([0.8,0.8,1])
		translate([p/2,0,L]) 
			cylinder(h=5, r=2.5, center=true);

	// LED Legs
	translate([0,0,0]) cube([0.2, 0.2, L]);
	translate([p,0,0]) cube([0.2, 0.2, L]);
}

module theLayer() {
	for (x=[0:7]) {
		for (y=[0:7]) {
			translate([p + x*s*p, p + y*s*p, 0]) led();
		}
	}
}

module theCube() {
	for (z=[0:7]) {
		translate([0,0,z*s*p]) theLayer();
	}
}

module chip(numPins) {
	chipZ = 2;
	chipWidth = 4;

	// Chip body
	translate([p/2,0.5,1])
		cube([(numPins+1)*p/2, chipWidth*p - 1, chipZ]);

	// Chip legs
	for (x=[1:numPins/2]) {
		translate([x*p,0,0]) cube([2,0.2,2]);
		translate([x*p,chipWidth*p,0]) cube([2,0.2,2]);
	}
}

module theChips() {
	for (y=[0:7]) {
		translate([p*s*(1), p*3 + p*s*y,0])
			chip(20);
	}
}