## QtPolly
This is an example library using AWS's [Amazon Polly](https://aws.amazon.com/polly/) service in a pure Qt/C++ Interface.

While this library is currently focused only on Amazon Polly's API, I am fairly certain it wouldn't be too difficult to adapt to other AWS services as well. 

## Why does this library exist?

Most AWS wrappers in Qt that I've seen were too bulky, out of date, and tend to fail on compile. Furthermore, [Amazon Polly](https://aws.amazon.com/polly/)  was a new feature added to AWS that none of the libraries had at the time.

Amazon does provide an [AWS SDK for C++](https://aws.amazon.com/sdk-for-cpp/), but it's an absolute monster and it's definitely not light weight whatsoever.

In search for a 'native' Qt API wrapper for AWS, I decided to just create one myself. The result is a simple, fast, and straightforward library for [Amazon Polly](https://aws.amazon.com/polly/). Theoretically this library should be able to request other AWS services that use similar endpoints as [Amazon Polly](https://aws.amazon.com/polly/), but YMMV.

## Usage

1. Include the `QtAws` library and header.
2. Initiate `QtAws` with your AWS Access and Secret Key
3. Connect the `requestStream` signal from `QtAws` to desired slot
4. Call the `requestPolly` function with text desired and 'voice' desired

Fully functional example is included in the `TestApplication` Application provided

## Available Voices to request from AWS Polly

When requesting a voice, use the name on the right of the dash in lowercase. For example, if you desire to use `English (en-US) - Joey`, request `joey`

   1. Welsh - Gwyneth
    2. Turkish  - Filiz
    3. Swedish  - Astrid
    4. Spanish (es-US) - Penelope
    5. Spanish (es-US) - Miguel
    6. Spanish (es-MX) - Mia
    7. Spanish (es-ES) - Conchita
    8. Spanish (es-ES) - Lucia
    9. Spanish (es-ES) - Enrique
    10. Russian - Tatyana
    11. Russian - Maxim
    12. Romanian - Carmen
    13. Portuguese (pt-PT) - Ines
    14. Portuguese (pt-PT) - Cristiano
    15. Portuguese (pt-BR) - Vitoria
    16. Portuguese (pt-BR)- Ricardo
    17. Polish - Ewa
    18. Polish - Maja
    19. Polish - Jacek
    20. Polish - Jan
    21. Norwegian - Liv
    22. Korean - Seoyeon
    23. Japanese - Mizuki
    24. Japanese - Takumi
    25. Italian - Carla
    26. Italian - Bianca
    27. Italian - Giorgio
    28. Icelandic - Dora
    29. Icelandic - Karl
    30. Hindi - Aditi
    31. French (fr-CA) - Chantal
    32. French (fr-FR) - Celine
    33. French (fr-FR) - Lea
    34. French (fr-FR) - Mathieu
    35. English (Welsh) - Geraint
    36. English (en-US) - Ivy
    37. English (en-US) - Joanna
    38. English (en-US) - Kendra
    39. English (en-US) - Kimberly
    40. English (en-US) - Salli
    41. English (en-US) - Joey
    42. English (en-US) - Justin
    43. English (en-US) - Matthew
    44. English (en-IN) - Aditi
    45. English (en-IN) - Raveena
    46. English (en-GB) - Amy
    47. English (en-GB) - Emma
    48. English (en-GB) - Brian
    49. English (en-AU) - Nicole
    50. English (en-AU) - Russell
    51. Dutch - Lotte
    52. Dutch - Ruben
    53. Danish - Naja
    54. Danish - Mads
    55. Chinese - Zhiyu
    56. Arabic - Zeina
