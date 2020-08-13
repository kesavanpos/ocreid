import { Component, OnInit } from "@angular/core";

import { Item } from "./item";
const firebase = require("nativescript-plugin-firebase");
import * as camera from "nativescript-camera";
import {ImageSource, fromFile, fromResource, fromBase64} from "tns-core-modules/image-source";


import {
    MLKitRecognizeTextResult,
    MLKitRecognizeTextResultBlock
  } from "nativescript-plugin-firebase/mlkit/textrecognition";

import { ObservableArray } from "tns-core-modules/data/observable-array";

const ImageCropper = require("nativescript-imagecropper").ImageCropper;
import { PhotoEditor, PhotoEditorControl } from "nativescript-photo-editor";
const parse = require('mrz').parse;


@Component({
    selector: "ns-items",
    templateUrl: "./items.component.html"
})
export class ItemsComponent  implements OnInit {
    items: Array<Item>;
    blocks: Array<MLKitRecognizeTextResultBlock>;
    imageSrc:any;
     // public items = ['item1', 'item2'];
     public itemsObs = new ObservableArray();
     public itemsObsBack = new ObservableArray();

    ngOnInit(): void {        
        this.imageSrc = "https://www.google.com/images/errors/logo_sm_2.png";
    }

    onTextRecognitionResult(scanResult)
    {
        const value: MLKitRecognizeTextResult = scanResult.value;
        this.blocks = value.blocks;
    }

    TapMrzReader(event)
    {
    }

    assignImage(imageSource,height,width)
    {
        var imageCropper = new ImageCropper();                              
        imageCropper.show(imageSource,{width:300,height:300}).then((args) => {
        console.log(args);
        if(args.image !== null){
            this.imageSrc = args.image;
        }
        })
        .catch(function(e){
        console.log(e);
        });
    }

    onBackCamera(event)
    {  
        camera.takePicture({
            width: 1800,
            height: 1800,
            keepAspectRatio: true,
            saveToGallery: false,
            cameraFacing: "rear"
        }).
        then((imageAsset) => {
            console.log("Result is an image asset instance");
            const source = new ImageSource();

            source.fromAsset(imageAsset)
                    .then((imageSource) => {   

                        firebase.mlkit.textrecognition.recognizeTextCloud({
                            image: imageSource 
                          }).then((result: MLKitRecognizeTextResult) => { 
                            console.log(result);
                          }).catch((e) =>{
                            console.log(e);
                          });
                        
                        firebase.mlkit.textrecognition.recognizeTextOnDevice({
                            image: imageSource 
                          }).then((result: MLKitRecognizeTextResult) => { 
                            console.log(result.text ? result.text : "");
                            this.itemsObsBack = new ObservableArray();      
                            let cardNumber,idNumber
                            for(let i = 0; i < result.blocks.length;i++)
                            {
                                if(result.blocks[i].text.indexOf("Number") >= 0)
                                {
                                    cardNumber = "ID Number :" + result.blocks[i].text;
                                    this.itemsObsBack.push(cardNumber.replace(/(\r\n|\n|\r)/gm," "));
                                }

                                if(result.blocks[i].text.indexOf("If you find this card, please") >= 0)
                                {
                                    idNumber = "Id Number : " + result.blocks[i + 1].text;
                                    this.itemsObsBack.push(idNumber.replace(/(\r\n|\n|\r)/gm," "));
                                }
                            }

                            result.blocks.forEach(element => {
                                const newItem = element.text;

                                if(newItem.indexOf("Resident") >= 0)
                                {
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Name") >= 0)
                                {
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Nationality") >= 0)
                                {
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                            });

                            result.blocks.forEach(element =>{
                                const newItem = element.text;

                                if(newItem.indexOf("Sex") >= 0){
                                    newItem.replace("s:ia","")
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Date of Birth") >= 0)
                                {
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Card Number") >= 0)
                                {
                                    this.itemsObsBack.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                            })

                            const photoEditor = new PhotoEditor();

                            photoEditor.editPhoto({
                                imageSource: imageSource,
                                hiddenControls: [
                                    PhotoEditorControl.Draw
                                ],
                            }).then((newImage: ImageSource) => {
                                // Here you can save newImage, send it to your backend or simply display it in your app
                                this.imageSrc = newImage;
                            }).catch((e) => {
                                console.error(e);
                            });

                            // let mrz = result.blocks[result.blocks.length - 1].text;
 
                            // var result1 = parse(mrz);

                            // this.itemsObsBack.push("MRZ : " + mrz);                            
                            
                            // this.itemsObsBack.push("DocumentCode : " + result1.fields.documentCode);                            
                            // this.itemsObsBack.push("IssuingState : " + result1.fields.issuingState);
                            // this.itemsObsBack.push("DocumentNumber : " + result1.fields.documentNumber);
                            // this.itemsObsBack.push("optional1 : " + result1.fields.optional1);

                            // this.itemsObsBack.push("BirthDate : " + result1.fields.birthDate);                            
                            // this.itemsObsBack.push("ExpirationDate : " + result1.fields.expirationDate);
                            // this.itemsObsBack.push("FirstName : " + result1.fields.firstName);
                            // this.itemsObsBack.push("LastName : " + result1.fields.lastName);

                            // this.itemsObsBack.push("Nationality : " + result1.fields.nationality);                            
                            // this.itemsObsBack.push("Sex : " + result1.fields.sex);

                          }).catch(errorMessage => console.log("ML Kit error: " + errorMessage));

                    }).catch((err) => {
                        console.log("Error -> " + err.message);
                    });
            })
    }

    takepicture()
    {
        camera.takePicture({
            width: 1200,
            height: 1200,
            keepAspectRatio: true,
            saveToGallery: false,
            cameraFacing: "rear"
        }).
        then((imageAsset) => {
            console.log("Result is an image asset instance");
            const source = new ImageSource();
            
            source.fromAsset(imageAsset)
                    .then((imageSource) => {                        
                        firebase.mlkit.textrecognition.recognizeTextOnDevice({
                            image: imageSource 
                          }).then((result: MLKitRecognizeTextResult) => { 
                            console.log(result.text ? result.text : "");
                            this.itemsObs = new ObservableArray();
                            let cardNumber,licenseno,idNumber;
                            for(let i = 0; i < result.blocks.length;i++)
                            {
                                if(result.blocks[i].text.indexOf("Number") >= 0)
                                {
                                    cardNumber = "ID Number :" + result.blocks[i + 1].text;
                                    this.itemsObs.push(cardNumber.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else
                                {
                                    
                                }
                                
                                if(result.blocks[i].text.indexOf("Driving") >= 0)
                                {
                                    licenseno = "License Number : " + result.blocks[i + 1].text;
                                    this.itemsObs.push(licenseno.replace(/(\r\n|\n|\r)/gm," "));
                                }

                                if(result.blocks[i].text.indexOf("If you find this card, please") >= 0)
                                {
                                    idNumber = "Id Number : " + result.blocks[i + 1].text;
                                    this.itemsObs.push(idNumber.replace(/(\r\n|\n|\r)/gm," "));
                                }
                            }

                            result.blocks.forEach(element => {
                                const newItem = element.text;

                                if(newItem.indexOf("Resident") >= 0)
                                {
                                    this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Name") >= 0)
                                {
                                    this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                                else if(newItem.indexOf("Nationality") >= 0)
                                {
                                    this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                }
                            });

                          }).catch(errorMessage => console.log("ML Kit error: " + errorMessage));
                          const photoEditor = new PhotoEditor();

                          photoEditor.editPhoto({
                              imageSource: imageSource,
                              hiddenControls: [
                                  PhotoEditorControl.Draw
                              ],
                          }).then((newImage: ImageSource) => {
                              // Here you can save newImage, send it to your backend or simply display it in your app
                              this.imageSrc = newImage;
                          }).catch((e) => {
                              console.error(e);
                          });

                    }).catch((err) => {
                        console.log("Error -> " + err.message);
                    });
            })
    }

    onTapCamera(event){

        camera.takePicture({
            width: 1200,
            height: 1200,
            keepAspectRatio: true,
            saveToGallery: false,
            cameraFacing: "rear"
        }).
        then((imageAsset) => {
            console.log("Result is an image asset instance");
            const source = new ImageSource();
            
            source.fromAsset(imageAsset)
                    .then((imageSource) => {                        
                        firebase.mlkit.textrecognition.recognizeTextOnDevice({
                            image: imageSource 
                          }).then((result: MLKitRecognizeTextResult) => { 
                            console.log(result.text ? result.text : "");
                            this.itemsObs = new ObservableArray();
                            let cardNumber,licenseno,idNumber;

                            if(result.blocks.filter(x => x.text.indexOf("ID Number") >= 0))
                            {
                                for(let i = 0; i < result.blocks.length;i++)
                                {
                                    if(result.blocks[i].text.indexOf("Number") >= 0)
                                    {
                                        cardNumber = "ID Number :" + result.blocks[i + 1].text;
                                        this.itemsObs.push(cardNumber.replace(/(\r\n|\n|\r)/gm," "));
                                    }                                
                                    
                                    if(result.blocks[i].text.indexOf("Driving") >= 0)
                                    {
                                        licenseno = "License Number : " + result.blocks[i + 1].text;
                                        this.itemsObs.push(licenseno.replace(/(\r\n|\n|\r)/gm," "));
                                    }

                                    if(result.blocks[i].text.indexOf("If you find this card, please") >= 0)
                                    {
                                        idNumber = "Id Number : " + result.blocks[i + 1].text;
                                        this.itemsObs.push(idNumber.replace(/(\r\n|\n|\r)/gm," "));
                                    }
                                }

                                result.blocks.forEach(element => {
                                    const newItem = element.text;
    
                                    if(newItem.indexOf("Resident") >= 0)
                                    {
                                        this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                    }
                                    else if(newItem.indexOf("Name") >= 0)
                                    {
                                        this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                    }
                                    else if(newItem.indexOf("Nationality") >= 0)
                                    {
                                        this.itemsObs.push(newItem.replace(/(\r\n|\n|\r)/gm," "));
                                    }
                                });

                                const photoEditor = new PhotoEditor();

                                photoEditor.editPhoto({
                                    imageSource: imageSource,
                                    hiddenControls: [
                                        PhotoEditorControl.Draw
                                    ],
                                }).then((newImage: ImageSource) => {
                                    // Here you can save newImage, send it to your backend or simply display it in your app
                                    this.imageSrc = newImage;
                                }).catch((e) => {
                                    console.error(e);
                                });
                            }
                            else
                            {
                                this.takepicture();
                            }

                          }).catch(errorMessage => console.log("ML Kit error: " + errorMessage));

                    }).catch((err) => {
                        console.log("Error -> " + err.message);
                    });
            })
    }
}
