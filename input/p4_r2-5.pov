camera {
  location  <0, 0, 10>
  up        <0,  1,  0>
  right     <1.33333, 0, 0>
  look_at   <0, 0, 0>
}

sphere { <2.95, 0.35, 2>, 2
  finish {ior 1.5}
}

sphere { <-2, 1, -1>, 3.5
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {reflection 0.0}
}

plane {<0, 1, 0>, -2.5
      pigment {color rgb <0.6, 0.1, 0.6>}
}

plane {<1, 1, 0>, -5
      pigment {color rgb <0.1, 0.1, 0.6>}
}
