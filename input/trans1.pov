camera {
  location  <0, 0, 18>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {
    <0, 11, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <8, 0, 0>, <0, 0, 8>
  }

light_source {
    <-11, -0.5, 0>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 9, 0>, <0, 0, 8>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.6, 0.1, 0.6>}
  scale <3.6, 1, 1>
  rotate <0, 0, 45>
  translate <0, 1 ,-2>
}

plane {<0, 1, 0>, -5
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<-1, 0, 0>, -7.1
      pigment {color rgb <0.8, 0.8, 0.1>}
}
