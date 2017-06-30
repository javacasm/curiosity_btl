$fn=30;

translate([4,-77.5,0])rotate([0,-90,-15])
translate([16.5,-9.5,0])
servo_bracket();

translate([-4,-77.5,0])cube([8,73.5,8]);

difference(){
cylinder(d=15,h=12.5);
translate([0,0,-1])cylinder(d=5.5,h=14);
}

rotate([0,0,145])
translate([-4,-70,0])cube([8,64.5,8]);

rotate([0,0,145])translate([0,-75,0])
difference(){
cylinder(d=15,h=10);
translate([0,0,-1])cylinder(d=5.5,h=12);
}

rotate([0,0,70]) translate([0,6,0])
linear_extrude(height=4)
polygon([[-4,0],[4,0],[3,20],[-3,20]]);

module servo_bracket(){
difference(){
union(){
translate([1,0,2])cube([35,19,4],center=true);
translate([0,9.5,2])
rotate([90,0,0])linear_extrude(height=19)
polygon([[-16.5,0],[16.5,0],[-16.5,8]]);
translate([13.75,0,0])cylinder(d=8,h=2,$fn=60);
}
cube([23.4,12.4,50],center=true);
translate([13.75,0,-1])cylinder(d=2.2,h=5,$fn=30);
translate([-13.75,0,-1])cylinder(d=2.2,h=50,$fn=30);
translate([13.75,0,2.5])cylinder(d=3.7,h=5,$fn=30);
translate([-13.75,0,2])cylinder(d=3.7,h=50,$fn=30);
translate([10,0,0])cylinder(d=6,h=12,$fn=60);
}
}
