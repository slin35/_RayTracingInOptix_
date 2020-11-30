camera {
  location  <0, 0, 18>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
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
  <0, 2, 0>, 3.1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

sphere { 
  <4.2, 2.35, 2>, 0.8
  pigment {
    image_map {jpg "../imgs/world.jpg"}
  }
}

sphere { 
   <-5.9, -0.5, 0>, 3.1
  pigment {
    image_map {jpg "../imgs/mosaic.jpg"}
  }

}

sphere { 
   <0, -35, 0>, 30
  pigment {
    image_map {bmp "../imgs/brick.bmp"}
  }
}

plane {<0, 0, 1>, -6 
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<1, 0, 0>, -14
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<-1, 1, 0>, -6.1
      pigment {color rgb <0.79, 0.61, 0.8>}
}
