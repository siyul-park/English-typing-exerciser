#include "Platform.h"

#include "ResourceSystem.h"

Resource * CreateResource(int _size, char * _fileName)
{
    int i, length, lastLength;

    Resource* resource;
    FILE* file_pointer;
    char buffer[INPUT_MAX];
    char ch;

    i = 0;
    lastLength = 0;
    length = 0;

    resource = (Resource*)malloc(sizeof(Resource));
    resource->size = _size;

    resource->Get = _Resource_Get;

    // ÆÄÀÏ »ýŒº
    file_pointer = fopen(_fileName, "a");
    if (file_pointer)
        fclose(file_pointer);
    file_pointer = fopen(_fileName, "r");

    if (file_pointer == NULL)
        return resource;

    while (i < resource->size)
    {
        if (!file_pointer)
            break;

        fscanf(file_pointer, "%s", buffer);

        length = strlen(buffer);

        if (length > 0)
        {
            if ((ch = fgetc(file_pointer)) == '\n' || ch == 0 || ch == EOF)
            {
                if (lastLength == 0)
                {
                    char* tmpStr = (char*)malloc(sizeof(char) * (length + 1));

                    strcpy(tmpStr, buffer);
                    resource->buffer[i] = tmpStr;
                }
                else
                {
                    lastLength += length;

                    char* tmpStr = (char*)malloc(sizeof(char) * (lastLength + length + 1));

                    strcpy(tmpStr, resource->buffer[i]);
                    strcat(tmpStr, buffer);

                    free(resource->buffer[i]);

                    resource->buffer[i] = tmpStr;
                }

                ++i;

                lastLength = 0;

                if (ch == EOF)
                    break;
            }
            else if (ch == ' ')
            {
                ++length;

                if (lastLength == 0)
                {
                    char* tmpStr = (char*)malloc(sizeof(char) * (length + 1));

                    strcpy(tmpStr, buffer);

                    tmpStr[length - 1] = ' ';
                    tmpStr[length] = 0;

                    resource->buffer[i] = tmpStr;
                }
                else
                {
                    char* tmpStr = (char*)malloc(sizeof(char) * (lastLength + length +1));

                    strcpy(tmpStr, resource->buffer[i]);
                    strcat(tmpStr, buffer);

                    buffer[lastLength + length - 1] = ' ';
                    buffer[lastLength + length] = 0;

                    free(resource->buffer[i]);

                    resource->buffer[i] = tmpStr;
                }

                lastLength += length;
            }
            
        }
        else
            break;

        while ((ch = fgetc(file_pointer)) == '\n' || ch == 0 || ch == EOF)
            ;
    }

    resource->size = i;

    fclose(file_pointer);

    return resource;

}

ResourceSystem * CreateResourceSystem(Application * _own)
{
    ResourceSystem* resourceSystem;
  
    resourceSystem = (ResourceSystem*)malloc(sizeof(ResourceSystem));

    resourceSystem->own = _own;
    resourceSystem->resource[WINDOWTYPE_INIT] = CreateResource(0, "RESOURCE_INIT.txt");
    resourceSystem->resource[WINDOWTYPE_SEATPRACTICE] = CreateResource(52, "RESOURCE_SEATPRACTICE.txt");
    resourceSystem->resource[WINDOWTYPE_WORDPRACTICE] = CreateResource(100, "RESOURCE_WORDPRACTICE.txt");
    resourceSystem->resource[WINDOWTYPE_SHORTSENTENCEPRACTICE] = CreateResource(30, "RESOURCE_SHORTSENTENCEPRACTICE.txt");
    resourceSystem->resource[WINDOWTYPE_LONGSENTENCEPRACTICE] = CreateResource(1, "RESOURCE_LONGSENTENCEPRACTICE.txt");

    resourceSystem->Get = _ResourceSystem_Get;

    return resourceSystem;
}

int DestroyResourceSystem(ResourceSystem * _resourceSystem)
{
    DestroyResource(_resourceSystem->resource[WINDOWTYPE_INIT]);
    DestroyResource(_resourceSystem->resource[WINDOWTYPE_SEATPRACTICE]);
    DestroyResource(_resourceSystem->resource[WINDOWTYPE_WORDPRACTICE]);
    DestroyResource(_resourceSystem->resource[WINDOWTYPE_SHORTSENTENCEPRACTICE]);
    DestroyResource(_resourceSystem->resource[WINDOWTYPE_LONGSENTENCEPRACTICE]);

    free(_resourceSystem);

    return 0;
}

int DestroyResource(Resource * _resource)
{
    int i;

    for (i = 0; i < _resource->size; ++i)
        free(_resource->buffer[i]);

    free(_resource);

    return 0;
}

char* _Resource_Get(Resource* _this)
{
    if (_this->size)
        return _this->buffer[rand() % _this->size];
    return 0;
}
char* _ResourceSystem_Get(ResourceSystem* _this, int _type)
{
    return _this->resource[_type]->Get(_this->resource[_type]);
}
