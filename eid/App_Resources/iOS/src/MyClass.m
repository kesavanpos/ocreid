#import "MyClass.h"

@implementation MyClass

- (NSString *)logInfo {
    
    NSError *error;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    NSString *dataPath = [documentsDirectory stringByAppendingPathComponent:@"/config"];
    NSLog(@"dataPath %@",dataPath);

     if (![[NSFileManager defaultManager] fileExistsAtPath:dataPath])
        [[NSFileManager defaultManager] createDirectoryAtPath:dataPath withIntermediateDirectories:NO attributes:nil error:&error]; //Create folder

        [self copyFilesToDocumentDirectory:@"config_ap" subFileName:@"config_ap"];
    [self copyFilesToDocumentDirectory:@"config_li" subFileName:@"config/config_li"];
    [self copyFilesToDocumentDirectory:@"config_lv_qa" subFileName:@"config/config_lv_qa"];
    [self copyFilesToDocumentDirectory:@"config_pg" subFileName:@"config/config_pg"];
    [self copyFilesToDocumentDirectory:@"config_tk_qa" subFileName:@"config/config_tk_qa"];
    [self copyFilesToDocumentDirectory:@"config_vg_qa" subFileName:@"config/config_vg_qa"];

    return dataPath;
}

-(void)copyFilesToDocumentDirectory:(NSString *)fileName subFileName:(NSString *)subFileName {
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    NSString *strPath = [self getDocumentDirectoryPath:subFileName];
    
    BOOL success = [fileManager fileExistsAtPath:strPath];
    
    if(!success) {
        NSString *defaultPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileName];
        NSLog(@"bundle Path %@",defaultPath);
        success = [fileManager copyItemAtPath:defaultPath toPath:strPath error:&error];
        
        if (!success)
            NSLog(@"%@ not created '%@'.",fileName, [error localizedDescription]);
        else
            NSLog(@"%@ created",fileName);
    }
}

-(NSString *)getDocumentDirectoryPath:(NSString *)stringPath {
    NSArray *arrPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory , NSUserDomainMask, YES);
    NSString *documentsDir = [arrPaths objectAtIndex:0];
    NSString *strValue = [NSString stringWithFormat:@"%@",[documentsDir stringByAppendingPathComponent:stringPath]];
    return strValue;
}

-(int)logInteger{
    return 56;
}

@end
