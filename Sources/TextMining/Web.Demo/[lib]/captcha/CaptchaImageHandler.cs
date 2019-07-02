﻿using System.Drawing;
using System.Drawing.Imaging;
using System.Web;

namespace captcha
{
    /// <summary>
    /// 
    /// </summary>
    public class CaptchaImageHandler : IHttpHandler
    {
        public bool IsReusable
        {
            get { return (true); }
        }

        public void ProcessRequest( HttpContext context )
        {
            HttpApplication applicationInstance = context.ApplicationInstance;
            string key = applicationInstance.Request.QueryString[ "guid" ];
            CaptchaImage image = null;
            if ( !string.IsNullOrEmpty( key ) )
            {
                if ( string.IsNullOrEmpty( applicationInstance.Request.QueryString[ "s" ] ) )
                {
                    image = (CaptchaImage) HttpRuntime.Cache.Get( key );
                }
                else
                {
                    image = (CaptchaImage) HttpContext.Current.Session[ key ];
                }
            }
            if ( image == null )
            {
                if ( key == "xz" )
                {
                    applicationInstance.Response.ContentType = "application/json";
                    applicationInstance.Context.Response.Write( "{ key: \"xz\" }" );
                    applicationInstance.Response.StatusCode = 200;
                    context.ApplicationInstance.CompleteRequest();
                }
                
                applicationInstance.Response.StatusCode = 404;
                context.ApplicationInstance.CompleteRequest();
            }
            else
            {
                using ( Bitmap bitmap = image.RenderImage() )
                {
                    bitmap.Save( applicationInstance.Context.Response.OutputStream, ImageFormat.Jpeg );
                }
                applicationInstance.Response.ContentType = "image/jpeg";
                applicationInstance.Response.StatusCode = 200;
                context.ApplicationInstance.CompleteRequest();
            }
        }
    }
}
