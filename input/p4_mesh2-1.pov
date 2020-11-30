camera {
  location  <0, 0, 15>
  up        <0,  1,  0>
  right     <1, 0,  0>
  look_at   <0, 0, 0>
}

light_source {
    <0, 11, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <10, 0, 0>, <0, 0, 10>
  }

light_source {
    <-13, -0.5, 0>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 9, 0>, <0, 0, 8>
}

sphere { 
   <0, 0, 0>, 1
  pigment {
    image_map {jpg "../imgs/mosaic.jpg"}
  }
  scale <30, 30, 30>
  rotate <80, 0, 0>
  translate <0, -32 ,0>
}


sphere { <-2.3, 2, 0>, 2.1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

obj {
  scale <2.5, 5.5, 2.5>
  rotate <0, 0, -11.5>
  translate <3, 1 ,0>
}

