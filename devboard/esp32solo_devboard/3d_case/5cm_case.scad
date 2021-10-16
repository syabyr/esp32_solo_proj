CORNER_RADIUS=3.3;
BOX_W = 50.2;
BOX_L = 50.2;
BOX_H = 10;
WALL_THICKNESS = 2;




//四周
module rander(){
    //cube(15,center=true);
    linear_extrude( BOX_H )
    difference(){
        offset(r=CORNER_RADIUS)
            square( [BOX_W-(CORNER_RADIUS-WALL_THICKNESS), BOX_L-(CORNER_RADIUS-WALL_THICKNESS)] ,center=true );
        offset( r= CORNER_RADIUS )
            square( [BOX_W-WALL_THICKNESS-CORNER_RADIUS, BOX_L-WALL_THICKNESS-CORNER_RADIUS] ,center=true);
    }
}


//4个安装孔

r_header=1.4;         //稍微小于m3的直径
r_height=6;          //底座高度+板厚:(2+1.4+1.6)
screw_offset = 22;      //螺丝孔的偏移量
dock_r=2.5;         //底座的半径,应该大于M3螺丝的半径(1.5mm)
dock_height=3.5;    //底座的高度=底板厚度+排针底部可能的高度(2+1.4)

module screw() {
    //螺丝孔
    translate([screw_offset,screw_offset,0])
    {
        cylinder(h=r_height,r=r_header-0.2);
    }
    translate([screw_offset,-screw_offset,0])
    {
        cylinder(h=r_height,r=r_header-0.2);
    }
    translate([-screw_offset,screw_offset,0])
    {
        cylinder(h=r_height,r=r_header);
    }
    translate([-screw_offset,-screw_offset,0])
    {
        cylinder(h=r_height,r=r_header);
    }
    //底座
    translate([screw_offset,screw_offset,0])
    {
        cylinder(h=dock_height,r=dock_r);
    }
    translate([screw_offset,-screw_offset,0])
    {
        cylinder(h=dock_height,r=dock_r);
    }
    translate([-screw_offset,screw_offset,0])
    {
        cylinder(h=dock_height,r=dock_r);
    }
    translate([-screw_offset,-screw_offset,0])
    {
        cylinder(h=dock_height,r=dock_r);
    }
}

module Base5CM(){
    union(){
        difference(){
        
            
        }
     rander();
        /*
     coordinates = [ [0,0],[0,BOX_L],[BOX_W,BOX_L],[BOX_W,0] ];
     translate ( [-BOX_W/2, -BOX_L/2] )
     hull()
     for (i = coordinates)
        translate(i) sphere(CORNER_RADIUS);
     */
        
        //底板
        linear_extrude( WALL_THICKNESS )
        offset(r=CORNER_RADIUS)
        square( [BOX_W-2, BOX_L-2] ,center=true );
        //固定孔
        screw();
       //translate([0,0,-21])
       //cube(50,center=true);
    }
}

//开孔部分
module Cut(){
    union(){
        //usb
        translate([0,-25,5+3])
        {
            cube([12,7,10],center = true);
        }
        //antenta
        translate([0,25,5+4])
        {
            cube([19,7,10-1.6],center = true);
        }
        
    }
}


module Base(){

difference(){
    Base5CM();
    Cut();
}
    

}


color("Green"){
	render(convexity=4) {
		Base();
	}
}