camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<2.0, 16.0, 12.0> color rgb <1.0, 1.0, 1.0>}

obj {
  pigment { color rgb <0.6, 0.1, 0.6>}
  scale <3.6, 1, 1>
  rotate <0, 0, 45>
  translate <0, 1 ,-2>
}


plane {<0, 1, 0>, -5
      pigment { color rgb <0.1, 0.1, 0.6>}
}