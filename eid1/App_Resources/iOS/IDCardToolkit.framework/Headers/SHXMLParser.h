//
//  SHXMLParser.h
//  SHXMLParser
//
//

#import <Foundation/Foundation.h>
#import "EIDAToolkitTypes.h"

@interface SHXMLParser : NSObject <NSXMLParserDelegate>

+ (NSArray *)convertDictionaryArray:(NSArray *)dictionaryArray toObjectArrayWithClassName:(NSString *)className classVariables:(NSArray *)classVariables;
+ (id)getDataAtPath:(NSString *)path fromResultObject:(NSDictionary *)resultObject;
- (NSDictionary *)parseData:(NSData *)XMLData;
+(NSString *)getencodedData:(void *)data;
+ (NSString*)base64forData:(NSData*)theData;
+(unsigned char *)convertString:(NSString *)str;
+(char *)convertFromString:(NSString *)str;
+(char *)stringEncode:(NSString *)str;
+(UInt8)ConvertTObyteArr:(unsigned char*)charValue;
+(NSMutableDictionary *)getencodedVGResponseValue:(VGRESPONSE_DATA)data;
+(NSMutableDictionary *)getencodedMrzValue:(MRZ_DATA)data;
+(NSMutableDictionary *)getencodedConfigCertValue:(CONFIG_CERT_EXPIRY_DATE)data;
@end
