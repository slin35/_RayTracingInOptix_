camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<2, 8, 7> color rgb <1.0, 1.0, 1.0>}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.2, 0.6, 0.8>}
  finish {reflection 0.4}
}

sphere { <0, -35, 0>, 33
  pigment { color rgb <0.8, 0.6, 0.2>}
  finish {reflection 0.8}
}
