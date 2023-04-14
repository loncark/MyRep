package com.loncar.composeapp.model

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "pictures_table")
@kotlinx.serialization.Serializable
data class Picture(
    @PrimaryKey val id: String,
    @ColumnInfo val handle: String,
    @ColumnInfo var description: String,
    @ColumnInfo var resource: String,
    @ColumnInfo val lat: String,
    @ColumnInfo val lng: String,
    @ColumnInfo var hashtags : String
)

/* Required for testing */
val dummyPictures = listOf(
    Picture("26","red", "I am only halfway there, this seems like an eternity.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred1.jpg?alt=media&token=776ada3b-f2a5-4f60-b196-2eecbd260b64",  "33.741916", "-84.486136", ""),
    Picture("27","red", "Do yourself a favor and autogenerate some random sentences next time.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred2.jpg?alt=media&token=343b6997-e1f5-44c3-9a15-13a9ae4ed6de", "38.479456", "-121.435369", ""),
    Picture("28","red", "Random sentences generator gave me rather dumb examples.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred3.jpg?alt=media&token=5c209084-f094-4a46-aba0-4012e0f1bb9b",  "32.707181", "-96.709623", ""),
    Picture("29","red", "Another short one.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred4.jpg?alt=media&token=8dbaa8ce-b5bf-4a08-9483-a4614ec1b5c5",  "38.573998", "-121.424383", ""),
    Picture("30","red", "Do other people have issues like this? Suppose so, perhaps I am too much of a Negative Nelly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred5.jpg?alt=media&token=9d1fe14c-46c0-41e2-b219-b336eb36fd6f",  "38.655013", "-121.436743", ""),
    Picture("31","red", "This is the 26th description to a dummy picture I have written.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred6.jpg?alt=media&token=b2899ff5-b8b3-4f50-a68a-01aa2be5a02a",  "47.686953", "-122.357866", ""),
    Picture("32","red", "I truly hope these pictures and descriptions will render correctly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred7.webp?alt=media&token=3c1331df-6275-4f9f-9e44-549e3b3f9baa", "33.771031", "-84.421591", ""),
    Picture("33","red", "Place your bets on how long it will take me to finish this app. I bet I am going to lose my senses before it happens.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred8.jpg?alt=media&token=af78ef93-1ac0-4978-80b3-51b4af69fe9e",  "32.694469", "-96.952695", ""),
)