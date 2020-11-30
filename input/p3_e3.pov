camera {
  location  <0, 0, 5>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {
    <0, 6, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <8, 0, 0>, <0, 0, 8>
  }

light_source {
    <-6, 4, -4>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 4, 0>, <0, 0, 4>
}

sphere { <1, 0, -4>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

sphere { <0, -35, 0>, 33
  pigment { color rgb <0.8, 0.6, 0.2>}
}

sphere { <2, 1, -1>, 0.5 
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

sphere { <-4.5, 1.2, -5>, 2.25
  pigment { color rgb <0.2, 0.6, 0.8>}
  finish {reflection 0.4}
}
