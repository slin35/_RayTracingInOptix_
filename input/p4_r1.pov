camera {
  location  <0, 0, 10>
  up        <0,  1,  0>
  right     <1.33333, 0, 0>
  look_at   <0, 0, 0>
}

sphere { <0, 0, 0>, 2
  finish {ior 1.5}
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.8, 0.2, 0.8>}
}
