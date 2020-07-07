import { Component, OnInit } from "@angular/core";
import { ActivatedRoute } from "@angular/router";

import { Item } from "./item";
import { ItemService } from "./item.service";

import { knownFolders, Folder, File,path } from "tns-core-modules/file-system";
import * as dialogs from "tns-core-modules/ui/dialogs";

declare var Toolkit: any;
declare var Initialize:any;
declare var IDCardToolkit:any;

@Component({
    selector: "ns-details",
    templateUrl: "./item-detail.component.html",
})
export class ItemDetailComponent implements OnInit {
    item: Item;

    constructor(
        private itemService: ItemService,
        private route: ActivatedRoute
    ) {}

    ngOnInit(): void {
        const id = +this.route.snapshot.params.id;
        this.item = this.itemService.getItem(id);

        const documents: Folder = <Folder>knownFolders.documents();
        const folder: Folder = <Folder>documents.getFolder("config");
        const tempExists: boolean = Folder.exists(folder.path);    
        

        const currentApp: Folder = <Folder>knownFolders.currentApp().getFolder("config");     

        const currentFile: File = <File>knownFolders.documents().getFile("config_li.txt");     
        const exists1 = File.exists(currentFile.path);

        const currentFile1: File = <File>knownFolders.documents().getFile("config_lv_qa.txt");     
        const exists2 = File.exists(currentFile1.path);

        const currentFile2: File = <File>knownFolders.documents().getFile("config_pg.txt");     
        const exists3 = File.exists(currentFile2.path);

        const currentFile3: File = <File>knownFolders.documents().getFile("config_tk_qa.txt");     
        const exists4 = File.exists(currentFile3.path);

        const currentFile4: File = <File>knownFolders.documents().getFile("config_vg_qa.txt");     
        const exists5 = File.exists(currentFile4.path);
        
        const mypath = path.join(folder.path, "/config_li.txt");
        const exists = File.exists(mypath);

        folder.getEntities()
            .then((entities) => {
                // entities is an array of files and folders.
                entities.forEach((entity) => {

                    dialogs.alert(entity.name).then(function() {
                        console.log("Dialog closed!");
                    });
                
                });
            }).catch((err) => {


                dialogs.alert(err).then(function() {
                    console.log("Dialog closed!");
                });
                // Failed to obtain folder's contents.
                console.log(err);
            });

        //var test = IDCardToolkitVersionString.value; 

        let configParams = "config_directory =" + folder.path + "/" + "\n";
        configParams += "&log_directory =" + folder.path + "/" + "\n";         
        configParams += "&read_publicdata_offline = true" + "\n";           
        configParams += "&vg_url=http://vg-pre-prod.ica.gov.ae/ValidationGatewayService";

        var objToolkit = Toolkit.new();      
        //try{
        //var toolkit = objToolkit.initConfigParamsError(0,configParams.toString());    
    }
}
