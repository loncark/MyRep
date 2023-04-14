package com.loncar.composeapp.logger

import java.time.LocalDateTime

interface Logger {
    fun templatePrint(user: String?) {
        print("User @$user ")
        actionPrint()
        print(" at ${LocalDateTime.now()}\n")
    }

    fun actionPrint()
}

class LoginLogger : Logger {
    override fun actionPrint() {
        print("logged in")
    }
}

class RegisterLogger : Logger {
    override fun actionPrint() {
        print("registered and logged in")
    }
}

class LogOutLogger : Logger {
    override fun actionPrint() {
        print("logged out")
    }
}