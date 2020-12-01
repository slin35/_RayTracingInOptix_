camera {
  location  <0, 0, 10>
  up        <0,  1,  0>
  right     <1.33333, 0, 0>
  look_at   <0, 0, 0>
}

sphere { <0, 0, 0>, 3
  finish {ior 1.5}
}

light_source {
    <0, 6, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <8, 0, 0>, <0, 0, 8>
  }


sphere { <-2.5, -2, 3>, 1
   pigment { image_map {png "me.png"} }
}

plane {<0, 1, 0>, -4
      pigment {color rgb <1.0, 1.0, 1.0>}
}

plane {<0, 0, 1>, -6 
      pigment {color rgb <0.1, 0.1, 0.6>}
      finish {reflection 0.0}
}

plane {<-1, 0, 0>, -5
      pigment {color rgb <0.8, 0.8, 0.1>}
      finish {reflection 0.0}
}

plane {<1, 0, 0>, -5
      pigment {color rgb <0.6, 0.1, 0.6>}
      finish {reflection 0.0}
}