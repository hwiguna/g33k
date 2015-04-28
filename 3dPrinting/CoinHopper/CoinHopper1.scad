materialHeight=2.35;
baseWidth = 81.7;
topWidth = 50.14;
height=28.5;

topNotchWidth=20; //TODO:Need to measure this!!!
topNotchDepth=3; //TODO:Need to measure this!!!

offset = (baseWidth - topWidth) / 2;

f_BaseWidth = 58.1;
f_TopWidth = 35.6;
f_offset = (f_BaseWidth - f_TopWidth);

//l_height = sqrt( pow((f_BaseWidth-f_TopWidth),2) + pow(height,2));
l_height = height+5;
l_baseWidth = baseWidth;
l_topWidth = topWidth;
l_offset = (l_baseWidth - l_topWidth) / 2;

module leftPiece()
{
	linear_extrude(height = materialHeight) 
		polygon(points=[[0,0],[l_offset,l_height],
				[l_offset+l_topWidth,l_height],[l_baseWidth,0],[0,0]]);
}

module backPiece()
{
	frontPiece();
}

module frontPiece() {
	linear_extrude(height = materialHeight) 
		polygon(points=[[0,0],[f_offset,height],
				[f_BaseWidth,height],[f_BaseWidth,0],[0,0]]);

	//TODO: Subtract the hole
}

module rightPiece() {

	topNotchOffset = offset + (topWidth-topNotchWidth) /2;

	difference()
	{
		linear_extrude(height = materialHeight) 
		polygon(points=[[0,0],[offset,height],
				[baseWidth-offset,height],[baseWidth,0],[0,0]]);

		translate([15.7,0,0]) cube([12.9, 2.45, 5]);
		translate([15.7+12.9+7.4,0,0]) cube([19.03, 5.15, 5]);

		translate([topNotchOffset,height-topNotchDepth,0]) 
			cube([topNotchWidth, topNotchDepth, 5]);
	}
}


rotate(60,v=[1,0,0]) frontPiece();

translate([f_BaseWidth,0,0])
	rotate(90,[0,1,0]) 
		rotate(90,[0,0,1])
			rightPiece();

translate([0,baseWidth,0])
	rotate(180-60,[1,0,0])
		backPiece();

rotate(180-48,[0,1,0])
	rotate(90,[0,0,1])
		leftPiece();