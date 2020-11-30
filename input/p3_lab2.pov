camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {
    <0, 4, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <4, 0, 0>, <0, 0, 4>
  }

light_source {
    <-4, 3, 2>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 2, 0>, <0, 0, 4>
}

sphere { <35, 0, 0>, 33
  pigment { color rgb <0.8, 0.8, 0.1>}
}

sphere { <2, 1, 1>, 0.5 
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

plane {<0, 1, 0>, -1.0
  pigment { color rgb <0.2, 0.6, 0.8>}
  finish {reflection 0.1}
}
