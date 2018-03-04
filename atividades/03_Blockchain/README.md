# DESCRIÇÃO COMPLEMENTAR DA ATIVIDADE

## Avisos

* A função ICHashCreate recebe 3 parâmetros: 1 ICHash com o nome **hash**, 1 ICBlockData com o nome **data**, e 1 ICHash com o nome **previousHash**. Esta função cria uma hash, apartir dos parâmetros **data** e **previousHash**. Esta hash criada nesta função é armazenada no parametro **hash**.
* O bloco gênesis, deve ter sua **hash** gerada com um valor de **data** qualquer e com a **previousHash** igual a zero.

## Restrições da Blockchain

* A blockchain deve possuir no máximo 100 blocos, sem contar o bloco gênesis.
* O array que representa a blockchain deve ser Singleton. Ou seja, só pode haver uma instância deste array e deve ser privada.
* Os nomes das funções devem seguir a convenção de nomes da Apple, do [Core Foundation](https://developer.apple.com/library/content/documentation/CoreFoundation/Conceptual/CFDesignConcepts/Articles/NamingConventions.html).
* A sigla do projeto que vamos utilizar será IC.

## Funções da Blockchain
* **Construtor**
  - Descrição: Cria uma blockchain. Ou seja, limpa o array que representa a cadeia, gera o bloco gênesis e adiciona-o na cadeia.
  - Parametros: Nenhum.
  - Retonos: Nenhum.

* **Obter o último bloco da cadeia**
  - Descrição: Retorna o último bloco adicionado à cadeia.
  - Parametros: Nenhum.
  - Retonos: O último bloco da cadeia. Retorna _NULL_ caso a cadeia não tenha sido criada.
  
* **Obter um bloco com índice n**
  - Descrição: Retorna o n-ésimo bloco à cadeia. Sendo o bloco zero o bloco gênesis.
  - Parametros: Um inteiro, que representa o índice do bloco na cadeia. Este índice se inicia com com 1 e vai até _BLOCKCHAIN_MAX_SIZE_. O bloco de índice 0 é o bloco gênesis.
  - Retonos: O bloco com o n-ésimo índice da cadeia. Caso o índice estiver fora dos limites, a função deve retornar o valor _NULL_.
  
* **Obter a cadeia**
  - Descrição: Retorna o array que representa a cadeia.
  - Parametros: Nenhum.
  - Retonos: Um array de blocos, que representa a cadeia e o tamanho da cadeia.
  
* **Minerar um novo bloco**
  - Descrição: Esta função é responsável por gerar um novo bloco e adiciona-lo na cadeia, a partir dos parâmetros da função.
  - Parametros: O endereço do emissor, o endereço do receptor, um inteiro representando a quantia transferida.
  - Retonos: Um boleano indicando se a operação foi realizada com sucesso. Se o tamanho da blockchain alcançar _BLOCKCHAIN_MAX_SIZE_, então o método deve retornar _false_. Caso contrário, ela deve retornar _true_.
  
* **Exibir um log da cadeia**
  - Descrição: Imprime na tela, ou em um arquivo, cada bloco da cadeia em sequência.
  - Parametros: Nenhum.
  - Retonos: Nenhum.
  
* **Verificar se a cadeia é válida**
  - Descrição: Verifica se cadeia de blocos é válida. Isto é, verifica, em cada bloco, se sua hash é válida e se ele aponta para a hash do bloco anterior. Não há a necessidade de verificar o bloco gênesis.
  - Parametros: Nenhum.
  - Retonos: Um boleano indicando se a cadeia é válida.
