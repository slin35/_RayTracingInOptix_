camera {
  location  <0, 0, 12>
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
  rotate <-80, 0, 0>
  translate <0, -32 ,0>
}

obj {
  scale <3, 3, 3>
  translate <2, 1 ,0>
}

