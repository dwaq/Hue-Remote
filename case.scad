
// x, y, z dimensions for switchmate
x_sm = 65;
y_sm = 125;
z_sm = 26;

// switchmate is mounted to the lightswitch
// which is this far off the wall 
z_lw = 6;

// total is both Z's added together
z_total = z_sm + z_lw;

// radius of the corners
r_corner = 11;

differenceca() {
cube([x_sm, y_sm, z_total],true);

translate([-(x_sm/2)+r_corner, -(y_sm/2)+r_corner, 0])
cylinder(z_total+1, r=r_corner, center=true);
}