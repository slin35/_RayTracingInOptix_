camera {
  location  <0, 18, 18>
  up        <0,  0.707,  -0.707>
  right     <1, 0,  0>
  look_at   <0, 0, 0>
}

sphere { 
  <0, 2, 0>, 3.1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

sphere { 
  <4.2, 2.35, 2>, 3.8
  pigment {
    image_map {jpg "world.jpg"}
  }
}

sphere { 
   <-5.9, -0.5, 0>, 3.1
  pigment {
    image_map {jpg "mosaic.jpg"}
  }
}

sphere { 
   <0, 0, 0>, 1
  pigment {
    image_map {jpg "Winslow_nebula.jpg"}
  }
  scale <30, 30, 30>
  rotate <-80, 0, 0>
  translate <0, -35 ,0>
}

