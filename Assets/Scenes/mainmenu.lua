Entities = {
    
    gameManager = {
        GameManager = {}
    },


    camera = {
        transform = {
            position = { x = 30, y = 10, z = 0 }
        },
        camera = {
            lookat = { x = 0, y = 10, z = 0 },
            name = "main",
            neardistance = 10,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  }
        }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "mainlight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0
        }
    },
 

    Background = {
        UITransform = {
            position = { x = 0, y = 0 },
            scale = { x = 1, y = 1},
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "mainbackground",
            materialName = "Main/background",
            zorder = 1
        }
    },
    Title = {

        UISpriteRenderer = {
            sprite = "maintitle",
            materialName = "Main/title",
            zorder = 2
        },
        UITransform = {
            position = { x = 0.20, y = 0.07 },
            scale = { x = 0.5, y = 0.4},
            rotation = 0
        }
    },
    PlayOneButton = {
	
        UIButtonScene = {
            sprite = "oneplayerbutton",
            materialName = "Main/OnePlayerbutton",
            scene = "race.lua",
            zorder = 3
        },

        UITransform = {
            position = { x = 0.1, y = 0.55 },
            scale = { x = 0.15, y = 0.15},
            rotation = 0
        }
    },
    
    PlayTwoButton = {
	
        UIButtonScene = {
            sprite = "twoplayerbutton",
            materialName = "Main/TwoPlayerbutton",
            scene = "race2.lua",
            zorder = 3
        },

        UITransform = {
            position = { x = 0.251, y = 0.55 },
            scale = { x = 0.15, y = 0.15},
            rotation = 0
        }
    },

    QuitButton = {
	
        UIButtonQuit = {
            sprite = "mainquitbutton",
            materialName = "Main/Quitbutton",
            zorder = 3
        },

        UITransform = {
            position = { x = 0.1, y = 0.71 },
            scale = { x = 0.3, y = 0.25},
            rotation = 0
        }
    }
    

}


