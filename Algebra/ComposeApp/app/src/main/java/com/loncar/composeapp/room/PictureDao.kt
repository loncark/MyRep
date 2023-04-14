package com.loncar.composeapp.room

import androidx.room.*
import com.loncar.composeapp.model.Picture

@Dao
interface PictureDao {
    @Query("SELECT * FROM pictures_table")
    suspend fun getAllPictures() : List<Picture>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun addAll(pictures: List<Picture>)

    @Insert
    suspend fun insertPicture(picture: Picture)

    @Update
    suspend fun update(picture: Picture)

}