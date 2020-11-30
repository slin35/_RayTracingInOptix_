camera {
  location  <0, 0, 22>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {
    <0, 11, 0>
    color rgb <2.5, 2.5, 1.5>
    area_light <10, 0, 0>, <0, 0, 10>
  }

light_source {
    <-13, -0.5, 0>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 9, 0>, <0, 0, 8>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.8, 0.8, 0.1>}
  scale <1.6, 0.1, 1.6>
  translate <2, 4, 4>
  rotate <6, 0, 0>
  rotate <0, 0, -6>
}

sphere { <0, 0, 0>, 3.5
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
  scale <2, 1, 1>
  rotate <0, 0, -45>
  translate <-4, 1, -1>
}

sphere { <6.5, 0, 5>, 1.5
  pigment { color rgb <0.2, 0.6, 0.8>}
  finish {reflection 0.4}
}

plane {<0, 1, 0>, -5
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<0, -1, 0>, -12
      pigment {color rgb <1.0, 1.0, 1.0>}
}

plane {<0, 0, 1>, -6
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<-1, 0, 0>, -16.1
      pigment {color rgb <1.0, 1.0, 1.0>}
}
