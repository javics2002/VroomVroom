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
            backgroundcolor = { r = .95, g = .4, b = .4, a = 1 }
        }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "mainlight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0,
            color = { r = .5, g = .5, b = .5 },
            ambientColor = { r = .5, g = .5, b = .5 }
        }
    },
 


    Title = {
        UISpriteRenderer = {
            sprite = "maintitle",
            materialName = "Main/title",
            zorder = 2
        },
        UITransform = {
            position = { x = 0.25, y = .08 },
            scale = { x = 0.2, y = .35},
            rotation = 0
        }
    },

    bandera1 = {

        UISpriteRenderer = {
            sprite = "bandera1",
            materialName = "Main/bandera1",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.44, y = 0.17 },
            scale = { x = 0.175, y = 0.31 },
            rotation = 1
        }
    },
    bandera2 = {

        UISpriteRenderer = {
            sprite = "bandera2",
            materialName = "Main/bandera2",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.1, y = 0.17 },
            scale = { x = 0.175, y = 0.31 },
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
            scale = { x = 0.1, y = 0.178 },
            rotation = 0
        }
    },

    background = {

        -- UISpriteRenderer = {
        --     sprite = "background",
        --     materialName = "Main/background",
        --     zorder = 0
        -- },
        -- UITransform = {
        --     position = { x = 0, y = 0 },
        --     scale = { x = 1, y = 1},
        --     rotation = 0
        -- }

        Transform = {
            position = { x = 200, y = 0, z = 0 },
            scale = { x = 1.8, y = 1, z = 1.8 },
            rotation = {x = 0, y = 0, z = 0}
        },
        meshrenderer = {
            mesh = "cube",
            meshName = "cube.mesh",
            materialName = "Main/background"
        }
    },

    CarOne = {
        Transform = {
            position = { x = 10, y = -2, z = 1.2 },
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
            position = { x = 15, y = -2, z = 5 },
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
            position = { x = 0.13, y = 0.5 },
            scale = { x = 0.095, y = 0.168 },
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
            position = { x = 0.205, y = 0.497 },
            scale = { x = 0.095, y = 0.169 },
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
            position = { x = 0.13, y = 0.68 },
            scale = { x = 0.168, y = 0.135 },
            rotation = 0
        }
    }
    

}


