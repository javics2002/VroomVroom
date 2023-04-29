Entities = {
    
    gameManager = {
        GameManager = {}
    },


    camera = {
        transform = {
            position = { x = 0, y = 0, z = 0 }
        },
        camera = {
            lookat = { x = 1, y = 0, z = 0 },
            name = "main",
            neardistance = 1,
            fardistance = 10000,
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
 


    Title = {

        UISpriteRenderer = {
            sprite = "maintitle",
            materialName = "Main/title",
            zorder = 2
        },
        UITransform = {
            position = { x = 0.25, y = 0.05 },
            scale = { x = 0.5, y = 0.5},
            rotation = 0
        }
    },

    Motor = {

        UISpriteRenderer = {
            sprite = "mainmotor",
            materialName = "Main/motor",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.85, y = 0.05 },
            scale = { x = 0.1, y = 0.1},
            rotation = 0
        }
    },

    CarOne = {
        Transform = {
            position = { x= 20, y = -4, z = 3 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 180, z = 0}
        },
        meshrenderer = {
            mesh = "kartone",
            meshName = "RedCar.mesh",
        }
	},

    CarTwo = {
        Transform = {
            position = { x= 20, y = -4.15, z = 10 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 180, z = 0}
        },
        meshrenderer = {
            mesh = "karttwo",
            meshName = "BlueCar.mesh",
        }
	},


    PlayOneButton = {
	
        UIButtonScene = {
            sprite = "oneplayerbutton",
            materialName = "Main/OnePlayerbutton",
            scene = "race.lua",
            playerlook = "carone",
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
            scene = "racetwo.lua",
            playerlook = "carone cartwo",
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


