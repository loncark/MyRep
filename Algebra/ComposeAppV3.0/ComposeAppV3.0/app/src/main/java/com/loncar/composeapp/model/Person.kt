package com.loncar.composeapp.model

@kotlinx.serialization.Serializable
data class Person(
    var email: String,
    val handle: String,
    var icon : String,
    var bio: String
)

/*
val dummyPersons = listOf(
    Person("blue", R.drawable.ic_launcher_background, "Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; In hac habitasse platea dictumst."),
    Person("red", R.drawable.ic_launcher_background, "Morbi non ullamcorper odio, nec sagittis nibh. In in est cursus, tincidunt felis vel, efficitur lorem. Cras maximus odio ut ante ultrices ultrices."),
    Person("green", R.drawable.ic_launcher_background, "Vestibulum fermentum mauris et lacinia molestie."),
    Person("purple", R.drawable.ic_launcher_background, "Suspendisse fringilla ut tortor at condimentum. Pellentesque luctus, ex nec luctus varius, nunc magna suscipit nulla, sed mollis orci elit sed eros."),
    Person("orange", R.drawable.ic_launcher_background, "Etiam efficitur augue vitae cursus rutrum."),
    Person("pink", R.drawable.ic_launcher_background, "Phasellus in tortor libero. Cras sodales urna ac lorem mollis tempus. Vivamus mattis dictum feugiat. Proin at libero euismod, imperdiet leo eu, pellentesque mauris. Sed pellentesque nulla eu enim rutrum ultrices."),
)
*/
