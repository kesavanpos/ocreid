import { Component, OnInit } from "@angular/core";
import { ActivatedRoute, ResolveEnd } from "@angular/router";

import { Item } from "./item";
import { ItemService } from "./item.service";

import { knownFolders, Folder, File,path } from "tns-core-modules/file-system";
import * as dialogs from "tns-core-modules/ui/dialogs";
import {discardedErrorEvent, uncaughtErrorEvent, UnhandledErrorEventData, on as applicationOn, run as applicationRun } from "tns-core-modules/application";

//import Initialize from "../../../typings/arm64/objc!IDCardToolkit.ts";

declare var Toolkit: any;
declare var Initialize:any;
declare var IDCardToolkit:any;
declare var MyClass:any;
declare var CardReader:any;


@Component({
    selector: "ns-details",
    templateUrl: "./item-detail.component.html",
})
export class ItemDetailComponent implements OnInit {
    item: Item;
    toolkit:any;
    cardReader:any;

    constructor(
        private itemService: ItemService,
        private route: ActivatedRoute
    ) {}

    ngOnInit():void {           
            const id = +this.route.snapshot.params.id;
            this.item = this.itemService.getItem(id);
    }

    async onTapToolkitVersion(args)
    {
        var readerarray = this.toolkit.listReadersAndReturnError();

        dialogs.alert(readerarray[0]).then(function() {
            console.log("Dialog closed!");
        });
    }
   
    async onTap(args)
    {
        const myClassInstance = new MyClass();
        let configFolderPath = myClassInstance.logInfo();   
        
        let configPath = myClassInstance.ShowConfigPath()+"/config";
        let logPath = myClassInstance.ShowLogPath()+"/config";

        const documents: Folder = <Folder>knownFolders.documents();
        const folder: Folder = <Folder>documents.getFolder("config");


        let folderPath = folder.path;

        let configParams = "config_directory =" + configPath + "/" + "\n";
        configParams += "&log_directory =" + logPath + "/" + "\n";         
        configParams += "&read_publicdata_offline = true" + "\n"; 
        configParams += "&vg_url=http://172.16.11.13/ValidationGatewayService";
                   
        var objToolkit = Toolkit.new();
       
        try{
        this.toolkit = await objToolkit.initConfigParamsError(1,configParams.toString());        
        dialogs.alert("Toolkit Intialized").then(function() {
            console.log("Dialog closed!");
        });

        var cardreader1 = CardReader.new();

        dialogs.alert("CardReader Connected is : " + cardreader1.isConnected()).then(function() {
            console.log("Dialog closed!");
        });

        this.cardReader = await this.toolkit.getReaderWithEmiratesIdAndReturnError();

        dialogs.alert("CardReader Name is : " + this.cardReader.getName()).then(function() {
            console.log("Dialog closed!");
        });


        var isConnected = this.cardReader.connectAndReturnError();

        dialogs.alert("CardReader Connected is : " + isConnected).then(function() {
            console.log("Dialog closed!");
        });

        

        // let options = {
        //     title: "EIDAToolkit",
        //     message: "EIDAToolkit Card Reader",
        //     okButtonText: "OK"
        // };

        // readerarray.forEach(element => {
        //     dialogs.alert(options).then(function() {
        //         console.log("Dialog closed!");
        //     });    
        // });
        
    }
    catch(e)
    {
        let options = {
            title: "EIDAToolkit Error",
            message: e.toString(),
            okButtonText: "OK"
        };
        dialogs.alert(options).then(function() {
            console.log("Dialog closed!");
        });
        console.log(e);
    }
    }
}
