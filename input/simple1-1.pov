camera {
  location  <-10, 0, 0>
  up        <0,  1,  0>
  right     <0, 0, 1.33333>
  look_at   <0, 0, 0>
}

light_source {<-12, 8, 7> color rgb <1.0, 1.0, 1.0>}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.8, 0.3, 0.3>}
}

sphere { <6, 0, -2>, 3.5
  pigment { color rgb <1.0, 1.0, 1.0>}
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.3, 0.0, 0.5>}
}
