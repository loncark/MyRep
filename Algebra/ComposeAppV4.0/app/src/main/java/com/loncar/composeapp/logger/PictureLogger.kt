package com.loncar.composeapp.logger

import java.time.LocalDateTime

interface PictureLogger {
    fun templatePrint(user: String, id: String) {
        print("User @$user ")
        actionPrint(id)
        print(" at ${LocalDateTime.now()}\n")
    }

    fun actionPrint(id: String)
}

class PictureUploadLogger : PictureLogger {
    override fun actionPrint(id: String) {
        print("uploaded a picture of id $id")
    }
}

class PictureUpdateLogger : PictureLogger {
    override fun actionPrint(id: String) {
        print("updated a picture of id $id")
    }
}

class PictureDeleteLogger : PictureLogger {
    override fun actionPrint(id: String) {
        print("deleted a picture of id $id")
    }
}