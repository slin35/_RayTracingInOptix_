camera {
  location  <0, 0, 10>
  up        <0,  1,  0>
  right     <1.33333, 0, 0>
  look_at   <0, 0, 0>
}


light_source {
    <0, 6, 0>
    color rgb <1.5, 1.5, 1.5>
    area_light <8, 0, 0>, <0, 0, 8>
  }

light_source {
    <-6, -4, -4>
    color rgb <2.0, 2.0, 4.0>
    area_light <0, 16, 0>, <0, 0, 4>
}

sphere { <0, 0, -1>, 2.5
  pigment { image_map {bmp "brick.bmp"} }
}


plane {<0, 1, 0>, -2.5
      pigment { image_map {bmp "brick.bmp"} }
}

plane {<1, 1, 0>, -5
      pigment {color rgb <0.1, 0.1, 0.6>}
}

plane {<-1, 0, 0>, -5
  pigment {color rgb <1.0, 0.9, 0>}
}

plane {<0, 0, 1>, -6 
      pigment {color rgb <0.1, 0.1, 0.8>}
}